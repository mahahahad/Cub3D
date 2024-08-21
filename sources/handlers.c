/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 22:14:20 by maabdull          #+#    #+#             */
/*   Updated: 2024/08/21 22:54:24 by maabdull         ###   ########.fr       */
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
	return (0);
}
