/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryagoub <ryagoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:46:40 by ryagoub           #+#    #+#             */
/*   Updated: 2024/08/26 20:31:51 by ryagoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void move_up(t_window_info **mlx)
{
	if((*mlx)->map[(int)round((*mlx)->player.y + sin(90 * (PI / 180)))/SQUARE][(int)round(((*mlx)->player.x)/SQUARE)] != '1')
		(*mlx)->player.y= (*mlx)->player.y + sin(90 * (PI / 180));
}
void move_down(t_window_info **mlx)
{
	if((*mlx)->map[((*mlx)->player.y + 20)/SQUARE][(((*mlx)->player.x)/SQUARE)] != '1')
		(*mlx)->player.y= (*mlx)->player.y + 5;
}
void move_right(t_window_info **mlx)
{
	if((*mlx)->map[(((*mlx)->player.y)/SQUARE)][(((*mlx)->player.x  + 20)/SQUARE)] != '1')
		(*mlx)->player.x= (*mlx)->player.x + 5;
}
void move_left(t_window_info **mlx)
{
	if((*mlx)->map[(int)round((*mlx)->player.y)/SQUARE][(int)round(((*mlx)->player.x - 5) /SQUARE)] != '1')
		(*mlx)->player.x = (*mlx)->player.x - 5;
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
