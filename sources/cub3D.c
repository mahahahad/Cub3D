/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:51:17 by maabdull          #+#    #+#             */
/*   Updated: 2024/08/21 22:51:36 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

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

int	main(int argc, char **argv)
{
	t_data		data;
	t_map		map;
	t_player	player;
	t_textures	textures;

	if (are_args_valid(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	map.fd = open(argv[1], O_RDONLY);
	if (map.fd < 0)
		return (ft_err("Map could not be opened. Does it exist?"));
	init_data(&data, &player, &map, &textures);
	if (process_map(&data) == EXIT_FAILURE)
		return (close(data.map->fd), EXIT_FAILURE);
	if (is_map_valid(&data) == EXIT_FAILURE)
		return (close(data.map->fd), free(data.map->full), \
			ft_freetab(map.grid), free_textures(data.textures), EXIT_FAILURE);
	print_info(data);
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, 1280, 720, "cub3D");
	mlx_hook(data.win_ptr, 17, 1L << 2, handle_destroy, &data);
	mlx_hook(data.win_ptr, 2, 1L << 0, handle_keypress, &data);
	mlx_loop(data.mlx_ptr);
	return (EXIT_SUCCESS);
}
