/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryagoub <ryagoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 22:14:20 by maabdull          #+#    #+#             */
/*   Updated: 2024/09/05 16:59:08 by ryagoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * @brief Cleanly destroy the window pointer from mlx and exit the game.
 *
 * @param data The struct containing all the variables that need freeing.
 * @return int
 */
int	handle_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	close(data->map->fd);
	free_textures(data->textures);
	ft_freetab(data->map->grid);
	exit(0);
	return (0);
}
void move_up(t_data *data)
{
	if(data->map->grid[(int)round (data->player->y - (SPEED * sin(data->player->angle  * (PI / 180))))/SQUARE]
		[(int)round (data->player->x + (SPEED * cos(data->player->angle  * (PI / 180))))/ SQUARE] != '1')
	{
		data->player->y =(int)round (data->player->y  - (SPEED * sin(data->player->angle  * (PI / 180))));
		data->player->x = (int)round (data->player->x + (SPEED * cos(data->player->angle  * (PI / 180))));
	}

}
void move_down(t_data *data)
{
	if(data->map->grid[(int)round (data->player->y + (SPEED * sin(data->player->angle  * (PI / 180))))/SQUARE]
		[(int)round (data->player->x - (SPEED * cos(data->player->angle  * (PI / 180))))/ SQUARE] != '1')
	{
		data->player->y =(int)round (data->player->y + (SPEED * sin(data->player->angle  * (PI / 180))));
		data->player->x = (int)round (data->player->x - (SPEED * cos(data->player->angle  * (PI / 180))));
	}
}
void move_right(t_data *data)
{
	if(data->map->grid[((data->player->y) / SQUARE)][((data->player->x  + 20)/SQUARE)] != '1')
		data->player->x= data->player->x + 5;
}
void move_left(t_data *data)
{
	if(data->map->grid[(int)round(data->player->y)/SQUARE][(int)round((data->player->x - 5) /SQUARE)] != '1')
		data->player->x = data->player->x - 5;
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == KEY_ESC)
		return (handle_destroy(data));
	if(keysym == 13)
		move_up(data);
	else if(keysym == 1)
		move_down(data);
	else if(keysym == 2)
		move_right(data);
	else if(keysym == 0)
		move_left(data);
	render_map(data);
	draw_player(data->player->x ,data->player->y, data);
	raycast(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	return (0);
}
