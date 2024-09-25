/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 22:14:20 by maabdull          #+#    #+#             */
/*   Updated: 2024/09/25 20:03:31 by maabdull         ###   ########.fr       */
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
	close(data->map->fd);
	free_textures(data->textures);
	ft_freetab(data->map->grid);
	exit(0);
	return (0);
}

void move_up(t_data *data)
{
	int new_y;
	int new_x; 

	data->player->velocity.y--;
	new_y = (int) round(data->player->y - \
		(SPEED * sin(data->player->angle * (PI / 180))));
	new_x = (int) round(data->player->x + \
		(SPEED * cos(data->player->angle * (PI / 180))));
	if(data->map->grid[new_y / SQUARE][new_x / SQUARE] != '1')
	{
		data->player->y = new_y;
		data->player->x = new_x;
	}
}

void move_down(t_data *data)
{
	int new_y;
	int new_x;

	data->player->velocity.y++;
	new_y = (int) round(data->player->y + \
		(SPEED * sin(data->player->angle * (PI / 180))));
	new_x = (int) round(data->player->x - \
		(SPEED * cos(data->player->angle * (PI / 180))));
	if(data->map->grid[new_y / SQUARE][new_x / SQUARE] != '1')
	{
		data->player->y =(int)round (data->player->y + (SPEED * sin(data->player->angle  * (PI / 180))));
		data->player->x = (int)round (data->player->x - (SPEED * cos(data->player->angle  * (PI / 180))));
	}
}

void move_right(t_data *data)
{
	int new_y;
	int new_x;

	data->player->velocity.x++;
	new_y = (int) round(data->player->y - \
		(SPEED * sin((data->player->angle - 90) * (PI / 180))));
	new_x = (int) round(data->player->x + \
		(SPEED * cos((data->player->angle - 90) * (PI / 180))));
	if(data->map->grid[(new_y / SQUARE)][new_x / SQUARE] != '1')
	{
		data->player->y = new_y;
		data->player->x = new_x;
	}
}

void move_left(t_data *data)
{
	int new_y;
	int new_x;

	data->player->velocity.x--;
	new_y = (int) round(data->player->y + \
		(SPEED * sin((data->player->angle - 90) * (PI / 180))));
	new_x = (int) round(data->player->x - \
		(SPEED * cos((data->player->angle - 90) * (PI / 180))));
	if(data->map->grid[(new_y / SQUARE)][new_x / SQUARE] != '1')
	{
		data->player->y = new_y;
		data->player->x = new_x;
	}
}

void	print_velocity(t_data *data)
{
	printf("x: %d\ny: %d\n", data->player->velocity.x, data->player->velocity.y);
}

int	handle_keyrelease(int keysym, t_data *data)
{
	if (keysym == KEY_W)
		data->player->velocity.y++;
	else if (keysym == KEY_A)
		data->player->velocity.x++;
	else if (keysym == KEY_S)
		data->player->velocity.y--;
	else if (keysym == KEY_D)
		data->player->velocity.x--;
	else if (keysym == KEY_ARROW_LEFT)
		data->player->angle_multiplier--;
	else if (keysym == KEY_ARROW_RIGHT)
		data->player->angle_multiplier++;
	// print_velocity(data);
	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == KEY_ESC)
		return (handle_destroy(data));
	else if (keysym == KEY_W)
		data->player->velocity.y--;
	else if (keysym == KEY_S)
		data->player->velocity.y++;
	else if (keysym == KEY_D)
		data->player->velocity.x++;
	else if (keysym == KEY_A)
		data->player->velocity.x--;
	else if (keysym == KEY_ARROW_LEFT)
		data->player->angle_multiplier++;
	else if (keysym == KEY_ARROW_RIGHT)
		data->player->angle_multiplier--;
	// print_velocity(data);
	return (0);
}
