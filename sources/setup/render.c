/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryagoub <ryagoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:01:22 by ryagoub           #+#    #+#             */
/*   Updated: 2024/08/26 22:36:33 by ryagoub          ###   ########.fr       */
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
	else if(c == '0' || c == 'N')
		return(0xF0C807);
	return(0);
}
void draw_player(int i, int j, t_data *data)
{
	int square_width;
	int square_height;
	int or_i;
	square_width = 0;
	square_height = 0;

	or_i = i;
	while (square_height < 20)
	{
		square_width= 0;
		i = or_i;
		while (square_width < 20)
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, i, j,0xFF8D85 );
			square_width++;
			i++;
		}
		j++;
		square_height++;
	}
}

void find_player_loc(t_data *data)
{
	int j;
	int i;
	int col ;
	int rows_count;

	i = 0;
	j = 0;
	col = 0;
	rows_count = 0;
	while(rows_count != data->map->rows)
	{
		i = 0;
		while (data->map->grid[j][i] != '\0')
		{
			if(data -> map->grid[j][i]== 'N' || data -> map->grid[j][i]== 'W'||data -> map->grid[j][i]== 'E'||data -> map->grid[j][i]== 'S')
			{
				data->player->direction = data->map->grid[j][i];
				data->player->x = i * SQUARE;
				data->player->y = j * SQUARE;
			}
			i++;
		}
		j++;
	}
}

void render_map(t_data data)
{
	int j;
	int i;
	int col ;

	i = 0;
	j = 0;
	col = 0;

	while(j != data.map->rows)
	{
		i = 0;
		while (i < ((int)ft_strlen(data.map->grid[j])))
		{
			col = return_color(data.map->grid[j][i]);
			draw_square(i * SQUARE, j* SQUARE, &data, col);
			i++;
		}
		j++;
	}
}


