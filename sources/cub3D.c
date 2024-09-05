/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryagoub <ryagoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:51:17 by maabdull          #+#    #+#             */
/*   Updated: 2024/09/04 23:11:52 by ryagoub          ###   ########.fr       */
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
void set_player_pixs(t_data *data)
{
	data->player->x = (data->player->x + 0.5) * SQUARE;
	data->player->y = (data->player->y + 0.5)* SQUARE;
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
	init_angle(&data);
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "cub3D");
	data.img.img = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
	data.img.img_pixels_ptr= mlx_get_data_addr(data.img.img,
												&(data.img.bits_per_pixel),
												&(data.img.line_len),
												&(data.img.endian));
	printf("My address is %p\n", data.img.img);
	if (data.img.img == NULL)
	{
		printf("error : img ptr\n");
		return (1);
	}
	set_player_pixs(&data);
	render_map(&data);
	draw_player(player.x , player.y , &data);
	raycast(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.img, 0, 0);
	printf("im here after raycasting its not seg faulting anymore\n");
	mlx_hook(data.win_ptr, 17, 1L << 2, handle_destroy, &data);
	mlx_hook(data.win_ptr, 2, 1L << 0, handle_keypress, &data);
	mlx_loop(data.mlx_ptr);
	return (EXIT_SUCCESS);
}
