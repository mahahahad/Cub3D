/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryagoub <ryagoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:01:22 by ryagoub           #+#    #+#             */
/*   Updated: 2024/09/27 18:41:58 by ryagoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	int	offset;
	if (y < 0 || y >= HEIGHT || x < 0 || x >= WIDTH)
		return ;

	offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));
	img->img_pixels_ptr[offset / 4] = color;
}

// void	my_pixel_put(t_img *img, int x, int y, int color)
// {
// 	int	offset;
// 	offset = ((img->line_len / 4) * y) + (x);
// 	*(offset + img->img_pixels_ptr) = color;
// }
// void	my_pixel_put(t_img *img, int x, int y, int color)
// {
// 	int	offset;
// 	offset = (Texture * y) + x;
// 	*(offset + img->img_pixels_ptr) = color;
// }
// void my_pixel_put(t_img *img, int x, int y, int color)
// {
//	int offset;
//	 unsigned int pixel_ptr;
//	 // Compute the byte offset for the pixel
//	 offset = ((img->line_len * y) + (x * (img->bits_per_pixel / 8)));
//	 // Calculate the pixel address and cast it to unsigned int *
//	 pixel_ptr = img->img_pixels_ptr[offset];
//	 // Set the color value at the computed address
//	 pixel_ptr = color;
// }

void	draw_square(int i, int j, t_data *data, int col)
{
	int	square_width;
	int	square_height;
	int	or_i;

	square_width = 0;
	square_height = 0;
	or_i = i;
	while (square_height < SQUARE - 1)
	{
		square_width = 0;
		i = or_i;
		while (square_width < SQUARE - 1)
		{
			my_pixel_put(&(data->img), i, j, col);
			square_width++;
			i++;
		}
		my_pixel_put(&(data->img), i, j, 0x000000);
		j++;
		square_height++;
	}
	my_pixel_put(&(data->img), i, j, 0x000000);
}

int	return_color(char c)
{
	if (c == '1')
		return (0x800080);
	else if (c == '0' || c == 'N' || c == 'W' || c == 'S' || c == 'E')
		return (0xF0C807);
	return (0x000000);
}

void	draw_player_stick(t_data *data)
{
	double	i;
	double	j;
	int		counter;

	i = (data->player->x) + 5;
	j = (data->player->y) + 5;
	counter = 0;
	if (data->player->angle == 90)
	{
		while (counter < 20)
		{
			my_pixel_put(&(data->img), i, j, 0xFF8D85);
			j--;
			counter++;
		}
	}
	else if (data->player->angle == 270)
	{
		while (counter < 20)
		{
			my_pixel_put(&(data->img), i, j, 0xFF8D85);
			j++;
			counter++;
		}
	}
	else if (data->player->angle == 0)
	{
		while (counter < 20)
		{
			my_pixel_put(&(data->img), i, j, 0xFF8D85);
			i++;
			counter++;
		}
	}
	else if (data->player->angle == 180)
	{
		while (counter < 20)
		{
			my_pixel_put(&(data->img), i, j, 0xFF8D85);
			i--;
			counter++;
		}
	}
	else
	{
		i = i + cos(data->player->angle * (PI / 180));
		j = j + sin(data->player->angle * (PI / 180));
		while (counter < 20)
		{
			my_pixel_put(&(data->img), i, j, 0xFF8D85);
			i++;
			j--;
			counter++;
		}
	}
}

int	rgb_to_hex(int rgb[3])
{
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

void	draw_background(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < (HEIGHT / 2))
	{
		i = 0;
		while (i < WIDTH)
		{
			my_pixel_put(&(data->img), i, j, \
				rgb_to_hex(data->textures->ceiling));
			i++;
		}
		j++;
	}
	while (j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			my_pixel_put(&(data->img), i, j, \
				rgb_to_hex(data->textures->floor));
			i++;
		}
		j++;
	}
}

void	draw_player(double i, double j, t_data *data)
{
	int	square_width;
	int	square_height;
	int	start_i;
	int	start_j;
	int	square_size;

	square_size = 10;
	start_i = i - square_size / 2;
	start_j = j - square_size / 2;
	square_height = 0;
	while (square_height < square_size)
	{
		square_width = 0;
		while (square_width < square_size)
		{
			my_pixel_put(&(data->img), start_i + square_width, \
				start_j + square_height, 0xFF8D85);
			square_width++;
		}
		square_height++;
	}
}

void	render_map(t_data *data)
{
	int	j;
	int	i;
	int	col ;

	i = 0;
	j = 0;
	col = 0;
	while (j < (data->map->rows))
	{
		i = 0;
		while (i < ((int) ft_strlen(data->map->grid[j])))
		{
			if (data->map->grid[j][i] != ' ')
			{
				col = return_color(data->map->grid[j][i]);
				draw_square(i * SQUARE, j * SQUARE, data, col);
			}
			i++;
		}
		j++;
	}
}
