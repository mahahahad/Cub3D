/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 22:14:20 by maabdull          #+#    #+#             */
/*   Updated: 2024/09/28 17:20:41 by maabdull         ###   ########.fr       */
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

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == KEY_ESC)
		return (handle_destroy(data));
	else if (keysym == KEY_W)
		data->player->velocity.y--;
	else if (keysym == KEY_S)
		data->player->velocity.y++;
	else if (keysym == KEY_D)
		data->player->velocity.x++;
	else if (keysym == KEY_A)
		data->player->velocity.x--;
	else if (keysym == KEY_ARROW_LEFT)
		data->player->angle_multiplier++;
	else if (keysym == KEY_ARROW_RIGHT)
		data->player->angle_multiplier--;
	return (0);
}

int	handle_keyrelease(int keysym, t_data *data)
{
	if (keysym == KEY_W)
		data->player->velocity.y++;
	else if (keysym == KEY_A)
		data->player->velocity.x++;
	else if (keysym == KEY_S)
		data->player->velocity.y--;
	else if (keysym == KEY_D)
		data->player->velocity.x--;
	else if (keysym == KEY_ARROW_LEFT)
		data->player->angle_multiplier--;
	else if (keysym == KEY_ARROW_RIGHT)
		data->player->angle_multiplier++;
	return (0);
}
