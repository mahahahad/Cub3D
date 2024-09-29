/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:26:14 by maabdull          #+#    #+#             */
/*   Updated: 2024/09/29 20:51:40 by maabdull         ###   ########.fr       */
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
	if (type == FLOOR && data->textures->floor[0] >= 0)
		return (ft_err("Duplicate floor texture detected."));
	if (type == CEILING && data->textures->ceiling[0] >= 0)
		return (ft_err("Duplicate ceiling texture detected."));
	return (EXIT_SUCCESS);
}

int	verify_colour(int texture_channels[3])
{
	if (texture_channels[0] < 0 || texture_channels[0] > 255)
		return (EXIT_FAILURE);
	if (texture_channels[1] < 0 || texture_channels[1] > 255)
		return (EXIT_FAILURE);
	if (texture_channels[2] < 0 || texture_channels[2] > 255)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

bool	is_num(char *num)
{
	int	i;

	i = 0;
	while (num[i])
	{
		if ((num[i] < '0' || num[i] > '9') && num[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}
