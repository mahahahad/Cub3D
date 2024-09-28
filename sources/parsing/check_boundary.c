/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_boundary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:40:02 by maabdull          #+#    #+#             */
/*   Updated: 2024/09/28 15:01:46 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_closed(t_data *data, char **visited, int x, int y)
{
	if (y < 0 || x < 0 || \
		y >= data->map->rows || x >= (int) ft_strlen(data->map->grid[y]))
		return (false);
	if (data->map->grid[y][x] == '1' || visited[y][x] == '1')
		return (true);
	else if (ft_strchr("0NEWS", data->map->grid[y][x]))
		visited[y][x] = '1';
	else if (x == 0 || ft_strchr(WHITESPACE, data->map->grid[y][x]) || \
		y == 0 || y == data->map->rows - 1)
		return (false);
	if (!is_closed(data, visited, x, y - 1) || \
		!is_closed(data, visited, x + 1, y) || \
		!is_closed(data, visited, x, y + 1) || \
		!is_closed(data, visited, x - 1, y))
		return (false);
	return (true);
}

/**
 * @brief Recursively spread outwards starting from the players position to
 * check if the tiles that are available to move to are enclosed within walls
 * or not.
 *
 * @param data
 * @return int
 */
int	is_surrounded_by_walls(t_data *data)
{
	char	**visited;

	visited = ft_tabdup(data->map->grid, 1);
	if (!is_closed(data, visited, data->player->x, data->player->y))
		return (ft_freetab(visited), \
			ft_err("Map must be surrounded by walls."));
	ft_freetab(visited);
	return (EXIT_SUCCESS);
}
