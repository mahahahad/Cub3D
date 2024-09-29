/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:43:01 by maabdull          #+#    #+#             */
/*   Updated: 2024/09/29 20:49:43 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_map(char *map_path, t_data *data)
{
	data->map->fd = 0;
	data->map->rows = 0;
	data->map->full = NULL;
	data->map->grid = NULL;
	data->map->fd = open(map_path, O_RDONLY);
	if (data->map->fd < 0)
		return (ft_err("Map could not be opened. Does it exist?"));
	return (EXIT_SUCCESS);
}

void	init_angle(t_data *data)
{
	if (data->player->direction == 'N')
		data->player->angle = 90;
	else if (data->player->direction == 'S')
		data->player->angle = 270;
	else if (data->player->direction == 'E')
		data->player->angle = 0;
	else if (data->player->direction == 'W')
		data->player->angle = 180;
}

void	init_textures(t_textures *textures)
{
	textures->north = NULL;
	textures->east = NULL;
	textures->west = NULL;
	textures->south = NULL;
	textures->floor[0] = -1;
	textures->floor[1] = -1;
	textures->floor[2] = -1;
	textures->ceiling[0] = -1;
	textures->ceiling[1] = -1;
	textures->ceiling[2] = -1;
}

void	init_player(t_player *player)
{
	player->direction = '\0';
	player->angle = 0;
	player->angle_multiplier = 0;
	player->x = 0;
	player->y = 0;
	player->velocity.x = 0;
	player->velocity.y = 0;
}

/**
 * @brief Allocates space for each child struct in the data struct
 *
 * @param t_data* data
*/
int	init_data(char *map_path, t_data *data)
{
	data->map = malloc(sizeof(t_map));
	data->player = malloc(sizeof(t_player));
	data->textures = malloc(sizeof(t_textures));
	if (init_map(map_path, data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	init_player(data->player);
	init_textures(data->textures);
	// data->mlx_ptr = NULL;
	// data->win_ptr = NULL;
	// data->hx = 0;
	// data->hy = 0;
	// data->vx = 0;
	// data->vy = 0;
	return (EXIT_SUCCESS);
}
