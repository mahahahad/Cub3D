/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryagoub <ryagoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 22:37:11 by maabdull          #+#    #+#             */
/*   Updated: 2024/09/27 15:05:48 by ryagoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	update_player(t_data *data, int x, int y)
{
	if (data->player->direction)
		return (ft_err("Multiple players found"));
	data->player->direction = data->map->grid[y][x];
	data->player->y = y ;
	data->player->x = x;
	return (EXIT_SUCCESS);
}

int	has_invalid_chars(t_data *data, t_player *player)
{
	int	x;
	int	y;

	y = -1;
	while (data->map->grid[++y])
	{
		x = -1;
		while (data->map->grid[y][++x])
		{
			if (!ft_strchr(WHITESPACE, data->map->grid[y][x]) \
				&& !ft_strchr("10NEWS", data->map->grid[y][x]))
				return (ft_err("Invalid character detected"));
			if (ft_strchr("NEWS", data->map->grid[y][x]))
				if (update_player(data, x, y) == EXIT_FAILURE)
					return (EXIT_FAILURE);
		}
	}
	if (!player->direction)
		return (ft_err("No player found"));
	data->map->rows = y;
	return (EXIT_SUCCESS);
}

int	are_textures_valid(t_data *data)
{
	if (open(data->textures->north, O_RDONLY) < 0)
		return (ft_err("North texture could not be opened."));
	else if (open(data->textures->east, O_RDONLY) < 0)
		return (ft_err("East texture could not be opened."));
	else if (open(data->textures->west, O_RDONLY) < 0)
		return (ft_err("West texture could not be opened."));
	else if (open(data->textures->south, O_RDONLY) < 0)
		return (ft_err("South texture could not be opened."));
	return (EXIT_SUCCESS);
}

int	has_required_config(t_data *data)
{
	if (!data->textures->north)
		return (ft_err("No north texture detected"));
	else if (!data->textures->east)
		return (ft_err("No east texture detected"));
	else if (!data->textures->west)
		return (ft_err("No west texture detected"));
	else if (!data->textures->south)
		return (ft_err("No south texture detected"));
	else if (are_textures_valid(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// else if (!data->textures->floor || !data->textures->floor[0])
	// 	return (ft_err("No floor colour detected"));
	// else if (!data->textures->ceiling || !data->textures->ceiling[0])
	// 	return (ft_err("No ceiling colour detected"));
	else if (!data->map->full)
		return (ft_err("No map found"));
	else if (has_invalid_chars(data, data->player) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	is_map_valid(t_data *data)
{
	data->map->grid = ft_split(data->map->full, '\n');
	if (has_required_config(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if (is_surrounded_by_walls(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
