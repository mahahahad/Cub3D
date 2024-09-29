/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:04:39 by ryagoub           #+#    #+#             */
/*   Updated: 2024/09/28 21:47:22 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	horizontal_distance(float ray_angle, t_data *data)
{
	float	x;
	float	y;
	float	x_new;
	float	y_new;

	if (ray_angle > 180)
		y = floor(data->player->y / SQUARE) * (SQUARE) + SQUARE;
	else
		y = floor(data->player->y / SQUARE) * (SQUARE) - 0.0001;
	x = data->player->x + (data->player->y - y) / tan(ray_angle * (PI / 180));
	while (check_all(data, x, y) == 0)
	{
		if (ray_angle > 180)
			y_new = SQUARE;
		else
			y_new = -SQUARE;
		x_new = SQUARE / tan(ray_angle * (PI / 180.0));
		if (ray_angle > 180)
			x -= x_new;
		else
			x += x_new;
		y += y_new;
	}
	return (data->hx = x, data->hy = y, cal_length(data, x, y));
}

float	vertical_distance(float ray_angle, t_data *data)
{
	float	x;
	float	y;
	float	x_new;
	float	y_new;

	if (ray_angle > 90 && ray_angle <= 270)
		x = floor(data->player->x / SQUARE) * (SQUARE) - 0.0001;
	else
		x = floor(data->player->x / SQUARE) * (SQUARE) + SQUARE;
	y = data->player->y + (data ->player->x - x) * tan(ray_angle * (PI / 180));
	while (check_all(data, x, y) == 0)
	{
		if (ray_angle > 90 && ray_angle <= 270)
			x_new = -SQUARE;
		else
			x_new = SQUARE;
		y_new = (float) SQUARE * tan(ray_angle * (PI / 180));
		if ((ray_angle > 0 && ray_angle < 90)
			|| (ray_angle > 270 && ray_angle <= 360))
			y -= y_new;
		else
			y += y_new;
		x += x_new;
	}
	return (data->vx = x, data->vy = y, cal_length(data, x, y));
}

float	wall_length(t_data *data, float ray_length, float ray_angle)
{
	float	ppd;
	float	wall_length;

	ray_length *= cos((ray_angle - data->player->angle) * (PI / 180));
	ppd = (WIDTH / 2) / tan(30 * (PI / 180));
	wall_length = (SQUARE / ray_length) * ppd;
	return (wall_length);
}

float	return_wall_length(t_data *data, float ray_angle, int rays_count)
{
	float	ver_dist;
	float	hor_dist;
	float	w_length;

	ver_dist = vertical_distance(ray_angle, data);
	hor_dist = horizontal_distance(ray_angle, data);
	if (ver_dist < hor_dist)
	{
		data->flag = 1;
		w_length = wall_length(data, ver_dist, ray_angle);
		draw_image(data, roundf(w_length), rays_count, ray_angle);
	}
	else
	{
		data->flag = 0;
		w_length = wall_length(data, hor_dist, ray_angle);
		draw_image(data, roundf(w_length), rays_count, ray_angle);
	}
	return (w_length);
}

void	raycast(t_data *data)
{
	float	step_angle;
	float	ray_angle;
	int		rays_count;
	int		i;

	ray_angle = data->player->angle + 30;
	if (ray_angle < 0)
		ray_angle += 360;
	if (ray_angle >= 360)
		ray_angle -= 360;
	step_angle = (float) 60 / (float) WIDTH;
	rays_count = 0;
	i = 0;
	while (rays_count < WIDTH)
	{
		return_wall_length(data, ray_angle, rays_count);
		ray_angle -= step_angle;
		if (roundf(ray_angle) <= 0)
			ray_angle = 360;
		rays_count++;
		i++;
	}
}
