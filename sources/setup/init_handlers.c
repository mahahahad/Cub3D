/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 22:05:18 by maabdull          #+#    #+#             */
/*   Updated: 2024/09/29 22:11:56 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

	ret_val = 0;
	mouse_x = 0;
	mouse_y = 0;
	mlx_mouse_get_pos(data->mlx_ptr, data->win_ptr, &mouse_x, &mouse_y);
	data->player->angle += -1 * (mouse_x - data->mouse_pos.x);
	data->mouse_pos.x = mouse_x;
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	update_player_info(data);
	raycast(data);
	ret_val = mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
		data->img.img, 0, 0);
	render_minimap(data);
	return (ret_val);
}

void	launch_handlers(t_data *data)
{
	mlx_hook(data->win_ptr, 2, 1L << 0, handle_keypress, data);
	mlx_hook(data->win_ptr, 3, 1L << 1, handle_keyrelease, data);
	mlx_hook(data->win_ptr, 17, 1L << 2, handle_destroy, data);
	mlx_loop_hook(data->mlx_ptr, update_frame, data);
	mlx_loop(data->mlx_ptr);
}
