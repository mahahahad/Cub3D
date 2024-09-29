/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:51:17 by maabdull          #+#    #+#             */
/*   Updated: 2024/09/29 22:07:58 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_mlx_data(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "cub3D");
	mlx_do_key_autorepeatoff(data->mlx_ptr);
	mlx_mouse_hide(data->mlx_ptr, data->win_ptr);
	mlx_mouse_move(data->mlx_ptr, data->win_ptr, WIDTH / 2, HEIGHT / 2);
	mlx_mouse_get_pos(data->mlx_ptr, data->win_ptr, &data->mouse_pos.x, \
		&data->mouse_pos.y);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (are_args_valid(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	data = (t_data *){0};
	data = malloc(sizeof(t_data));
	if (init_data(argv[1], data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (process_map(data) == EXIT_FAILURE)
		return (close(data->map->fd), EXIT_FAILURE);
	if (is_map_valid(data) == EXIT_FAILURE)
		return (close(data->map->fd), free(data->map->full), \
			ft_freetab(data->map->grid), free_textures(data->textures), \
			EXIT_FAILURE);
	init_player_data(data);
	if (init_mlx_data(data) == EXIT_FAILURE \
		|| init_images(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	launch_handlers(data);
	return (EXIT_SUCCESS);
}
