/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:51:17 by maabdull          #+#    #+#             */
/*   Updated: 2024/08/19 00:33:36 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * @brief Cleanly destroy the window pointer from mlx and exit the game.
 * 
 * @param data The struct containing all the variables that need freeing.
 * @return int 
 */
int	handle_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(0);
	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == KEY_ESC)
		return (handle_destroy(data));
	return (0);
}

/**
 * @brief Read a file, using the provided file descriptor `fd` completely.
 * 
 * @param fd The file descriptor pointing to the open file to be read.
 * @return char* The full contents of the file
 */
char	*read_file(int fd)
{
	char	*line;
	char	*buffer;
	char	*temp;

	buffer = malloc(1);
	temp = NULL;
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		temp = buffer;
		buffer = ft_strjoin(buffer, line);
		free(line);
		free(temp);
	}
	return (buffer);
}

int	main(int argc, char **argv)
{
	t_data	data;
	char	*map;

	if (argc != 2)
		return (ft_putendl_fd("Error\nPlease enter a map file.", 2), 1);
	map = read_file(open(argv[1], O_RDONLY));
	ft_putendl_fd(map, 1);
	free(map);
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, 1280, 720, "cub3D");
	mlx_hook(data.win_ptr, 17, 1L << 2, handle_destroy, &data);
	mlx_hook(data.win_ptr, 2, 1L << 0, handle_keypress, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
