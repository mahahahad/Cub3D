/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryagoub <ryagoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:01:22 by ryagoub           #+#    #+#             */
/*   Updated: 2024/08/30 16:22:44 by ryagoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void  draw_square(int i, int j,t_data *data, int col)
{
	int square_width;
	int square_height;
	square_width = 0;
	square_height = 0;
	int or_i;
	or_i = i;
	while (square_height < SQUARE - 1)
	{
		square_width= 0;
		i = or_i;
		while (square_width < SQUARE - 1)
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, i, j, col);
			square_width++;
			i++;
		}
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, i, j, 0x000000);
		j++;
		square_height++;
	}
	mlx_pixel_put(data->mlx_ptr, data->win_ptr, i, j, 0x000000);
}
int return_color(char c)
{
	if (c == '1')
		return(0x800080);
	else if(c == '0' || c == 'N' || c == 'W'|| c == 'S'|| c == 'E')
		return(0xF0C807);
	return(0x000000);
}
void draw_player_stick(t_data *data)
{
	double i;
	double j;
	i = (data->player->x ) + 5;
	j = (data->player->y) + 5;
	int counter;
	counter = 0;
	if(data->player->angle == 90)
	{
		while(counter < 20)
		{
				mlx_pixel_put(data->mlx_ptr, data->win_ptr,i , j,0xFF8D85 );
				j--;
				counter++;
		}
	}
	else if(data->player->angle == 270)
	{
		while(counter < 20)
		{
				mlx_pixel_put(data->mlx_ptr, data->win_ptr,i , j,0xFF8D85 );
				j++;
				counter++;
		}
	}
	else if(data->player->angle == 0)
	{
		while(counter < 20)
		{
				mlx_pixel_put(data->mlx_ptr, data->win_ptr,i , j,0xFF8D85 );
				i++;
				counter++;
		}
	}
	else if(data->player->angle == 180)
	{
		while(counter < 20)
		{
				mlx_pixel_put(data->mlx_ptr, data->win_ptr,i , j,0xFF8D85 );
				i--;
				counter++;
		}
	}
	else
	{
		i = i + (cos(data->player->angle *(PI / 180)));
		j =j + (sin(data->player->angle *(PI / 180)));
		while(counter < 20)
		{
				mlx_pixel_put(data->mlx_ptr, data->win_ptr,i , j,0xFF8D85 );
				i++;
				j--;
				counter++;
		}
	}
}

void draw_player(double i, double j, t_data *data)
{
	int square_width;
	int square_height;
	int or_i;
	square_width = 0;
	square_height = 0;

	or_i = i;
	while (square_height < 10)
	{
		square_width= 0;
		i = or_i;
		while (square_width < 10)
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, i, j,0xFF8D85 );
			square_width++;
			i++;
		}
		j++;
		square_height++;
	}
	draw_player_stick(data);
}


void render_map(t_data *data)
{
	int j;
	int i;
	int col ;

	i = 0;
	j = 0;
	col = 0;
	while(j < (data->map->rows) )
	{
		i = 0;
		while (i < ((int)ft_strlen(data->map->grid[j])))
		{
			if(data->map->grid[j][i] != ' ')
			{
				col = return_color(data->map->grid[j][i]);
				draw_square(i * SQUARE, j* SQUARE, data, col);
			}
			i++;
		}
		j++;
	}
}


