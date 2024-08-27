/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryagoub <ryagoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:46:40 by ryagoub           #+#    #+#             */
/*   Updated: 2024/08/28 00:11:05 by ryagoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void move_up(t_data *data)
{
	if(data->map->grid[(int)round(data->player->y + sin(90 * (PI / 180)))/SQUARE][(int)round((data->player->x)/SQUARE)] != '1')
		data->player->y= data->player->y + sin(90 * (PI / 180));
}
void move_down(t_data *data)
{
	if(data->map->grid[(data->player->y + 20)/SQUARE][((data->player->x)/SQUARE)] != '1')
		data->player->y= data->player->y + 5;
}
void move_right(t_data *data)
{
	if(data->map->grid[((data->player->y)/SQUARE)][((data->player->x  + 20)/SQUARE)] != '1')
		data->player->x= data->player->x + 5;
}
void move_left(t_data *data)
{
	if(data->map->grid[(int)round(data->player->y)/SQUARE][(int)round((data->player->x - 5) /SQUARE)] != '1')
		data->player->x = data->player->x - 5;
}

// int move(int key,t_window_info **mlx)
// {
// 	if(key == 13)
// 		move_up(mlx);
// 	else if(key == 1)
// 		move_down(mlx);
// 	else if(key == 2)
// 		move_right(mlx);
// 	else if(key == 0)
// 		move_left(mlx);
// 	render_map(*mlx);
// 	draw_player((*mlx)->player.x,(*mlx)->player.y, (*mlx));
// 	return(0);
// }
