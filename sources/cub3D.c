/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:51:17 by maabdull          #+#    #+#             */
/*   Updated: 2024/09/18 23:02:43 by maabdull         ###   ########.fr       */
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
		printf("Floor colour: ");
		printf("%d, %d, %d\n", data.textures->floor[0], data.textures->floor[1], data.textures->floor[2]);
	}
	if (data.textures->ceiling)
	{
		printf("Ceiling colour: ");
		printf("%d, %d, %d\n", data.textures->ceiling[0], data.textures->ceiling[1], data.textures->ceiling[2]);
	}
	if (data.map->full)
	{
		puts("\nMap: ");
		puts(data.map->full);
	}
}

void set_player_pixs(t_data *data)
{
	data->player->x = (data->player->x * SQUARE) + (SQUARE / 2) ;
	data->player->y = (data->player->y * SQUARE) + (SQUARE / 2) ;
}

/**
 * @brief Update the players location and angle in the data struct
 * based on the keys currently being pressed
 * 
 * @param data 
 */
void	update_player_info(t_data *data)
{
	data->player->x += data->player->x * data->player->velocity.x * SPEED;
	data->player->y += data->player->y * data->player->velocity.y * SPEED;
	data->player->angle += data->player->angle_multiplier;
	data->player->angle %= 360;
}

int	update_frame(t_data *data)
{
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	update_player_info(data);
	draw_background(data);
	raycast(data);
	// printf("%d %d %d %d\n", data->player->velocity.x, data->player->velocity.y, data->player->angle_multiplier, data->player->angle);
	return (mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0));
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	init_data(data);
	if (are_args_valid(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	data->map->fd = open(argv[1], O_RDONLY);
	if (data->map->fd < 0)
		return (ft_err("Map could not be opened. Does it exist?"));
	if (process_map(data) == EXIT_FAILURE)
		return (close(data->map->fd), EXIT_FAILURE);
	if (is_map_valid(data) == EXIT_FAILURE)
		return (close(data->map->fd), free(data->map->full), \
			ft_freetab(data->map->grid), free_textures(data->textures), EXIT_FAILURE);
	print_info(*data);
	init_angle(data);
	data->mlx_ptr = mlx_init();
	mlx_do_key_autorepeatoff(data->mlx_ptr);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "cub3D");
	data->img.img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img.img_pixels_ptr = (int *) (mlx_get_data_addr(data->img.img,
												&(data->img.bits_per_pixel),
												&(data->img.line_len),
												&(data->img.endian)));
	if (data->img.img == NULL)
	{
		ft_err("Image could not be created");
		return (1);
	}
	// printf("hello\n");
	set_player_pixs(data);
	// render_map(data);
	// draw_player(data->player->x, data->player->y , data);
	save_images(data);
	// if (!data->south || !data->north)
	// 	return(1);
	// draw_background(data);
	// raycast(data);
	// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	// printf("im here after raycasting its not seg faulting anymore\n");
	mlx_hook(data->win_ptr, 2, 1L << 0, handle_keypress, data);
	mlx_hook(data->win_ptr, 3, 1L << 1, handle_keyrelease, data);
	mlx_hook(data->win_ptr, 17, 1L << 2, handle_destroy, data);
	mlx_loop_hook(data->mlx_ptr, update_frame, data);
	mlx_loop(data->mlx_ptr);
	return (EXIT_SUCCESS);
}
