/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:43:01 by maabdull          #+#    #+#             */
/*   Updated: 2024/08/21 22:54:55 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_map(t_map *map)
{
	map->rows = 0;
	map->full = NULL;
	map->grid = NULL;
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
	player->x = '\0';
	player->y = '\0';
}

void	init_data(t_data *data, t_player *player, t_map *map, \
	t_textures *textures)
{
	init_map(map);
	init_player(player);
	init_textures(textures);
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->map = map;
	data->player = player;
	data->textures = textures;
}
