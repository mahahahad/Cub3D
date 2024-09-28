/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 22:05:12 by maabdull          #+#    #+#             */
/*   Updated: 2024/09/28 19:13:56 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_map(char *processed_line, char *line, t_data *data, bool found)
{
	if (!processed_line[0] && data->map->full)
		return (free(processed_line), ft_err("Empty line found in map"));
	if (processed_line[0] == '1' || processed_line[0] == '0')
		return (append_map_content(data, processed_line, line));
	if (processed_line[0] != '\0' && !found)
		return (free(processed_line), ft_err("Invalid character detected."));
	free(processed_line);
	return (EXIT_SUCCESS);
}

/**
 * @brief Set the various structs inside the data struct as appropriate using
 * the provided line.
 *
 * Loop through the provided texture_ids to identify if the line is a texture
 * line by comparing the starting of the line with the provided texture_ids.
 * If it matches, pass it to the `assign_textures` function with the direction
 * identifier removed. This makes it easy to remove the whitespaces separating
 * the identifier and the path.
 *
 * @param line
 * @param data
 * @return int
 */
int	set_game_data(char *line, t_data *data)
{
	int		i;
	char	*processed_line;
	char	*t_ids[7];
	bool	found;

	i = -1;
	found = false;
	set_texture_ids(t_ids);
	processed_line = ft_strtrim(line, WHITESPACE);
	while (t_ids[++i])
	{
		if (!ft_strncmp(processed_line, t_ids[i], ft_strlen(t_ids[i])))
		{
			if (assign_texture(i, processed_line + ft_strlen(t_ids[i]), \
				data) == EXIT_FAILURE)
				return (free_textures(data->textures), \
					free(processed_line), EXIT_FAILURE);
			found = true;
			break ;
		}
	}
	return (check_map(processed_line, line, data, found));
}

/**
 * @brief Read the map in the data struct character by character and check for
 * newlines. Once found, send the full line to the `set_game_data` function
 * which sets the appropriate structs in the data struct.
 *
 * @param data
 */
int	process_map(t_data *data)
{
	char	*line;
	char	read_buffer[2];
	char	*temp;
	int		output;

	line = ft_strdup("");
	output = 1;
	while (output)
	{
		output = read(data->map->fd, read_buffer, 1);
		if (!output)
			break ;
		read_buffer[output] = '\0';
		temp = line;
		line = ft_strjoin(line, read_buffer);
		free(temp);
		if (read_buffer[0] == '\n')
		{
			if (set_game_data(line, data) == EXIT_FAILURE)
				return (free(line), EXIT_FAILURE);
			free(line);
			line = ft_strdup("");
		}
	}
	return (free(line), EXIT_SUCCESS);
}

int	assign_texture(t_texture_type type, char *texture, t_data *data)
{
	if (data->map->full)
		return (free_textures(data->textures), free(texture), \
			ft_err("Misplaced texture path found."));
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

int	set_rgb_values(int texture_channels[3], char *line)
{
	char	**str_color_values;

	while (*line == ' ')
		line++;
	str_color_values = ft_split(line, ',');
	if (ft_tablen(str_color_values) != 3 \
		|| !is_num(str_color_values[0]) \
		|| !is_num(str_color_values[1]) \
		|| !is_num(str_color_values[2]))
		return (ft_err("Incorrect colour format provided."));
	texture_channels[0] = ft_atoi(str_color_values[0]);
	texture_channels[1] = ft_atoi(str_color_values[1]);
	texture_channels[2] = ft_atoi(str_color_values[2]);
	if (verify_colour(texture_channels) == EXIT_FAILURE)
		return (ft_err("Colours must be in 0 - 255 range."));
	ft_freetab(str_color_values);
	return (EXIT_SUCCESS);
}
