/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:01:22 by ryagoub           #+#    #+#             */
/*   Updated: 2024/09/29 22:09:37 by maabdull         ###   ########.fr       */
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

int	rgb_to_hex(int rgb[3])
{
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

int	get_pixel_color(char c)
{
	if (c == '1')
		return (0x000000);
	if (c == '0' || c == 'N' || c == 'E' || c == 'W' || c == 'S')
		return (0xFFFFFF);
	return (0x000000);
}

void	draw_square(int i, int j, t_data *data, int col)
{
	int	square_width;
	int	square_height;
	int	or_i;

	square_width = 0;
	square_height = 0;
	or_i = i;
	while (square_height < GRID_PIX_SIZE)
	{
		square_width = 0;
		i = or_i;
		while (square_width < GRID_PIX_SIZE)
		{
			my_pixel_put(&(data->minimap), i, j, col);
			square_width++;
			i++;
		}
		j++;
		square_height++;
	}
}

/**
 * @brief Loop through each cell in the map grid and draw a small square for it 
 * in the minimap image.
 * 
 * @param data 
 */
int	render_minimap(t_data *data)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (j < data->map->rows)
	{
		i = 0;
		while (i < (int) ft_strlen(data->map->grid[j]))
		{
			if (data->map->grid[j][i] != ' ')
				draw_square(i * GRID_PIX_SIZE, j * GRID_PIX_SIZE, data, \
					get_pixel_color(data->map->grid[j][i]));
			i++;
		}
		j++;
	}
	draw_square((int)(data->player->x / SQUARE) * GRID_PIX_SIZE, \
		(int)(data->player->y / SQUARE) * GRID_PIX_SIZE, data, 0x00FF00);
	return (mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
		data->minimap.img, 16, 16));
}
