/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 22:37:11 by maabdull          #+#    #+#             */
/*   Updated: 2024/09/05 13:22:38 by maabdull         ###   ########.fr       */
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
	else if (!data->textures->floor)
		return (ft_err("No floor texture detected"));
	else if (!data->textures->ceiling)
		return (ft_err("No ceiling texture detected"));
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
