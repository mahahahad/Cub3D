/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:26:14 by maabdull          #+#    #+#             */
/*   Updated: 2024/09/18 22:56:23 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_texture_ids(char *texture_ids[7])
{
	texture_ids[0] = "NO";
	texture_ids[1] = "EA";
	texture_ids[2] = "WE";
	texture_ids[3] = "SO";
	texture_ids[4] = "F";
	texture_ids[5] = "C";
	texture_ids[6] = NULL;
}

int	append_map_content(t_data *data, char *processed_line, char *line)
{
	char	*temp;

	if (!data->map->full)
		data->map->full = ft_strdup("");
	temp = data->map->full;
	data->map->full = ft_strjoin(data->map->full, line);
	return (free(temp), free(processed_line), EXIT_SUCCESS);
}

bool	is_set(t_data *data, t_texture_type type)
{
	if (type == NORTH && data->textures->north)
		return (ft_err("Duplicate north texture detected."));
	if (type == EAST && data->textures->east)
		return (ft_err("Duplicate east texture detected."));
	if (type == WEST && data->textures->west)
		return (ft_err("Duplicate west texture detected."));
	if (type == SOUTH && data->textures->south)
		return (ft_err("Duplicate south texture detected."));
	if (type == FLOOR && data->textures->floor[0])
		return (ft_err("Duplicate floor texture detected."));
	if (type == CEILING && data->textures->ceiling[0])
		return (ft_err("Duplicate ceiling texture detected."));
	return (EXIT_SUCCESS);
}

int	set_rgb_values(int texture_channels[3], char *line)
{
	char	**str_color_values;

	str_color_values = ft_split(line, ',');
	if (ft_tablen(str_color_values) != 3)
		return (ft_err("Incorrect colour format provided."));
	texture_channels[0] = ft_atoi(str_color_values[0]);
	texture_channels[1] = ft_atoi(str_color_values[1]);
	texture_channels[2] = ft_atoi(str_color_values[2]);
	ft_freetab(str_color_values);
	return (EXIT_SUCCESS);
}

int	assign_texture(t_texture_type type, char *texture, t_data *data)
{
	if (is_set(data, type) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (type == NORTH)
		data->textures->north = ft_strtrim(texture, WHITESPACE);
	else if (type == EAST)
		data->textures->east = ft_strtrim(texture, WHITESPACE);
	else if (type == WEST)
		data->textures->west = ft_strtrim(texture, WHITESPACE);
	else if (type == SOUTH)
		data->textures->south = ft_strtrim(texture, WHITESPACE);
	else if (type == FLOOR)
	{
		if (set_rgb_values(data->textures->floor, texture) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (type == CEILING)
	{
		if (set_rgb_values(data->textures->ceiling, texture) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
