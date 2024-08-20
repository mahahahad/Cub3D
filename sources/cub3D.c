/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:51:17 by maabdull          #+#    #+#             */
/*   Updated: 2024/08/20 21:12:48 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

void	free_textures(t_textures *textures)
{
	if (textures->north)
		free(textures->north);
	if (textures->east)
		free(textures->east);
	if (textures->west)
		free(textures->west);
	if (textures->south)
		free(textures->south);
	if (textures->floor)
		free(textures->floor);
	if (textures->ceiling)
		free(textures->ceiling);
}

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
	exit(0);
	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == KEY_ESC)
		return (handle_destroy(data));
	return (0);
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
	if (type == FLOOR && data->textures->floor)
		return (ft_err("Duplicate floor texture detected."));
	if (type == CEILING && data->textures->ceiling)
		return (ft_err("Duplicate ceiling texture detected."));
	return (0);
}

int	assign_texture(t_texture_type type, char *texture, t_data *data)
{
	if (is_set(data, type))
		return (1);
	if (type == NORTH)
		data->textures->north = ft_strtrim(texture, WHITESPACE);
	else if (type == EAST)
		data->textures->east = ft_strtrim(texture, WHITESPACE);
	else if (type == WEST)
		data->textures->west = ft_strtrim(texture, WHITESPACE);
	else if (type == SOUTH)
		data->textures->south = ft_strtrim(texture, WHITESPACE);
	else if (type == FLOOR)
		data->textures->floor = ft_strtrim(texture, WHITESPACE);
	else if (type == CEILING)
		data->textures->ceiling = ft_strtrim(texture, WHITESPACE);
	return (0);
}

/**
 * @brief Set the various structs inside the data struct as appropriate using
 * the provided line.
 * 
 * Loop through the provided keywords to identify if the line is a texture line
 * by comparing the starting of the line with the provided keywords.
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
	char	*processed_line;
	char	*keywords[] = {"NO", "EA", "WE", "SO", "F", "C", NULL};
	int		i = 0;
	char	*temp;

	processed_line = ft_strtrim(line, WHITESPACE);
	if (processed_line[0] == '0')
		return (free_textures(data->textures), \
			free(processed_line), \
			ft_err("Map must be surrounded by walls"));
	if (processed_line[0] == '1')
	{
		if (!data->map->full)
			data->map->full = ft_strdup("");
		temp = data->map->full;
		data->map->full = ft_strjoin(data->map->full, line);
		return (free(temp), free(processed_line), 0);
	}
	while (keywords[i])
	{
		if (!ft_strncmp(processed_line, keywords[i], ft_strlen(keywords[i])))
		{
			if (data->map->full)
				return (free_textures(data->textures), \
					free(processed_line), \
					ft_err("Misplaced texture path found."));
			if (assign_texture(i, \
				processed_line + ft_strlen(keywords[i]), \
				data) == 1)
				return (free_textures(data->textures), \
					free(processed_line), 1);
			break ;
		}
		i++;
	}
	free(processed_line);
	return (0);
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
	temp = NULL;
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
			if (set_game_data(line, data) == 1)
				return (free(line), 1);
			free(line);
			line = ft_strdup("");
		}
	}
	free(line);
	return (0);
}

bool	is_valid_ext(char *file_name)
{
	int	len;
	char	*ext;

	len = ft_strlen(file_name);
	if (len <= 4)
		return (false);
	ext = ft_substr(file_name, len - 4, 4);
	if (ft_strncmp(ext, ".cub", 4))
		return (free(ext), false);
	return (free(ext), true);
}

void	print_info(t_data data)
{
	puts("Texture Paths: ");
	if (data.textures->north)
	{
		printf("North texture: ");
		puts(data.textures->north);
	}
	if (data.textures->east)
	{
		printf("East texture: ");
		puts(data.textures->east);
	}
	if (data.textures->west)
	{
		printf("West texture: ");
		puts(data.textures->west);
	}
	if (data.textures->south)
	{
		printf("South texture: ");
		puts(data.textures->south);
	}
	if (data.textures->floor)
	{
		printf("Floor texture: ");
		puts(data.textures->floor);
	}
	if (data.textures->ceiling)
	{
		printf("Ceiling texture: ");
		puts(data.textures->ceiling);
	}
	if (data.map->full)
	{
		puts("\nMap: ");
		puts(data.map->full);
	}
}

bool	has_invalid_chars(char *map_full)
{
	int	i;

	i = 0;
	while (map_full[i])
	{
		if (!ft_strchr(WHITESPACE, map_full[i]) \
			&& !ft_strchr("10NEWS", map_full[i]))
			return (ft_err("Invalid character detected"));
		i++;
	}
	return (false);
}

int	verify_map(t_data *data)
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
	else if (has_invalid_chars(data->map->full))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_map	map;
	t_textures	textures;

	if (argc != 2)
		return (ft_err("Please enter a map file."));
	if (!is_valid_ext(argv[1]))
		return (ft_err("Please enter a .cub map file"));
	map.fd = open(argv[1], O_RDONLY);
	if (map.fd < 0)
		return (ft_err("Map could not be opened."));
	data.map = &map;
	data.textures = &textures;
	if (process_map(&data) == 1)
		return (close(map.fd), 1);
	if (verify_map(&data) == 1)
		return (close(map.fd), free_textures(data.textures), 1);
	print_info(data);
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, 1280, 720, "cub3D");
	mlx_hook(data.win_ptr, 17, 1L << 2, handle_destroy, &data);
	mlx_hook(data.win_ptr, 2, 1L << 0, handle_keypress, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
