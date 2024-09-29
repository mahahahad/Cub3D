/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:51:17 by maabdull          #+#    #+#             */
/*   Updated: 2024/09/29 19:59:59 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

void	update_velocity(t_data *data, float *new_x, float *new_y)
{
	if (data->player->velocity.y == -1)
	{
		*new_y += -sin(data->player->angle * PI / 180);
		*new_x += cos(data->player->angle * PI / 180);
	}
	if (data->player->velocity.x == -1)
	{
		*new_y += -cos(data->player->angle * PI / 180);
		*new_x += -sin(data->player->angle * PI / 180);
	}
	if (data->player->velocity.y == 1)
	{
		*new_y += sin(data->player->angle * PI / 180);
		*new_x += -cos(data->player->angle * PI / 180);
	}
	if (data->player->velocity.x == 1)
	{
		*new_y += cos((data->player->angle) * PI / 180);
		*new_x += sin((data->player->angle) * PI / 180);
	}
}
void	move_player(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = 0.0;
	new_y = 0.0;
	update_velocity(data, &new_x, &new_y);
	if (data->map->grid[(int)(data->player->y) / SQUARE]
		[(int)(data->player->x + new_x * 4) / SQUARE] != '1')
		data->player->x += new_x;
	if (data->map->grid[(int)(data->player->y + new_y * 4) / SQUARE]
		[(int)(data->player->x) / SQUARE] != '1')
		data->player->y += new_y;
}

/**
 * @brief Update the players location and angle in the data struct
 * based on the keys currently being pressed
 *
 * @param data
 */
void	update_player_info(t_data *data)
{
	move_player(data);
	data->player->angle += data->player->angle_multiplier;
	if (data->player->angle < 0)
		data->player->angle += 360;
	data->player->angle %= 360;
}

int	update_frame(t_data *data)
{
	int	ret_val;
	int	mouse_x;
	int	mouse_y;

	mouse_x = 0;
	mouse_y = 0;
	mlx_mouse_get_pos(data->mlx_ptr, data->win_ptr, &mouse_x, &mouse_y);
	data->player->angle += -0.9 * (mouse_x - data->mouse_pos.x);
	data->mouse_pos.x = mouse_x;
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	update_player_info(data);
	raycast(data);
	ret_val = mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, 
		data->img.img, 0, 0);
	render_minimap(data);
	return (ret_val);
}

// int	handle_mouse_move(int x, int y, t_data *data)
// {
// 	printf("%d %d %d\n", data->player->angle, data->mouse_pos.x, x);
// 	data->mouse_pos.x = x;
// 	data->mouse_pos.y = y;
// 	return (0);
// }

int	create_minimap_image(t_data *data)
{
	data->minimap.img = mlx_new_image(data->mlx_ptr, (data->map->max_cols + 1) \
		* GRID_PIX_SIZE, data->map->rows * GRID_PIX_SIZE);
	if (data->minimap.img == NULL)
		return (ft_err("Image could not be created"));
	data->minimap.img_pixels_ptr = (int *)(mlx_get_data_addr(data->minimap.img,
		&(data->minimap.bits_per_pixel),
		&(data->minimap.line_len),
		&(data->minimap.endian)));
	return (EXIT_SUCCESS);
}

int	create_render_image(t_data *data)
{
	data->img.img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (data->img.img == NULL)
		return (ft_err("Image could not be created"));
	data->img.img_pixels_ptr = (int *)(mlx_get_data_addr(data->img.img,
		&(data->img.bits_per_pixel),
		&(data->img.line_len),
		&(data->img.endian)));
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (are_args_valid(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	data = (t_data*) {0};
	data = malloc(sizeof(t_data));
	if (init_data(argv[1], data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (process_map(data) == EXIT_FAILURE)
		return (close(data->map->fd), EXIT_FAILURE);
	if (is_map_valid(data) == EXIT_FAILURE)
		return (close(data->map->fd), free(data->map->full), \
			ft_freetab(data->map->grid), free_textures(data->textures), \
			EXIT_FAILURE);
	init_angle(data);
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "cub3D");
	mlx_do_key_autorepeatoff(data->mlx_ptr);
	// mlx_mouse_hide(data->mlx_ptr, data->win_ptr);
	// mlx_mouse_move(data->mlx_ptr, data->win_ptr, WIDTH / 2, HEIGHT / 2);
	mlx_mouse_get_pos(data->mlx_ptr, data->win_ptr, &data->mouse_pos.x, &data->mouse_pos.y);
	create_render_image(data);
	create_minimap_image(data);
	data->player->x = (data->player->x * SQUARE) + (SQUARE / 2);
	data->player->y = (data->player->y * SQUARE) + (SQUARE / 2);
	if (save_images(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	mlx_hook(data->win_ptr, 2, 1L << 0, handle_keypress, data);
	mlx_hook(data->win_ptr, 3, 1L << 1, handle_keyrelease, data);
	mlx_hook(data->win_ptr, 17, 1L << 2, handle_destroy, data);
	// mlx_hook(data->win_ptr, 6, 1L << 6, handle_mouse_move, data);
	mlx_loop_hook(data->mlx_ptr, update_frame, data);
	mlx_loop(data->mlx_ptr);
	return (EXIT_SUCCESS);
}
