/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:43:01 by maabdull          #+#    #+#             */
/*   Updated: 2024/09/05 13:18:58 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_map(t_map *map)
{
	map->fd = 0;
	map->rows = 0;
	map->full = NULL;
	map->grid = NULL;
}

void init_angle(t_data *data)
{
	if(data ->player->direction == 'N')
		data->player->angle = 90;
	else if(data->player->direction == 'S')
		data->player->angle = 270;
	else if(data->player->direction == 'E')
		data->player->angle = 0;
	else if(data->player->direction == 'W')
		data->player->angle = 180;
}

void	init_textures(t_textures *textures)
{
	textures->north = NULL;
	textures->east = NULL;
	textures->west = NULL;
	textures->south = NULL;
	textures->floor = NULL;
	textures->ceiling = NULL;
}

void	init_player(t_player *player)
{
	player->direction = '\0';
	player ->angle = '\0';
	player->x = '\0';
	player->y = '\0';
}

/**
 * @brief Allocates space for each child struct in the data struct
 *
 * @param t_data* data
*/
void	init_data(t_data *data)
{
	data->map = malloc(sizeof(t_map));
	data->player = malloc(sizeof(t_player));
	data->textures = malloc(sizeof(t_textures));
	init_map(data->map);
	init_player(data->player);
	init_textures(data->textures);
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->hx =0;
	data->hy = 0;
	data->vx = 0;
	data->vy = 0;
}
