/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:18:16 by ryagoub           #+#    #+#             */
/*   Updated: 2024/09/28 18:04:30 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_img	get_image(t_data *data, float ray_angle, int flag)
{
	if (flag == 0)
	{
		if (ray_angle < 180)
			return (data->north);
		else
			return (data->south);
	}
	else if (ray_angle > 90 && ray_angle < 270)
		return (data->east);
	return (data->west);
}

float	get_x(t_data *data, float ray_angle)
{
	float	x_text;

	if (data->flag == 0)
	{
		x_text = (int) data->hx % TEXTURE ;
		if (ray_angle > 180)
			x_text = 31 - x_text;
	}
	if (data->flag == 1)
	{
		x_text = (int) data->vy % TEXTURE;
		if (ray_angle > 90 && ray_angle < 270)
			x_text = 31 - x_text;
	}
	return (x_text);
}

int	get_color(t_data *data, int x, int y, float ray_angle)
{
	t_img	image;
	int		*image_in_pixs;
	int		color;
	int		offset;

	image = get_image(data, ray_angle, data->flag);
	offset = (y * (image.line_len / 4) + x);
	image_in_pixs = image.img_pixels_ptr;
	color = *(image_in_pixs + offset);
	return (color);
}

int	calc_offset(int *wall_length)
{
	int		ty_off;

	ty_off = 0;
	if ((int)(*wall_length) > HEIGHT)
	{
		ty_off = ((int)(*wall_length) - HEIGHT) / 2.0;
		*wall_length = HEIGHT;
	}
	return (ty_off);
}

void	draw_image(t_data *data, int wall_length, int rays_count, \
	float ray_angle)
{
	int		count;
	int		y;
	float	step;
	float	y_text;
	float	x_text;

	step = (1.0 * TEXTURE) / wall_length;
	count = 0;
	y = 0;
	while (y < (HEIGHT / 2) - ((int) wall_length / 2))
		my_pixel_put(&(data->img), rays_count, y++,
			rgb_to_hex(data->textures->ceiling));
	y_text = calc_offset(&wall_length) * step;
	while (count < (int) wall_length)
	{
		x_text = get_x(data, ray_angle);
		my_pixel_put(&(data->img), rays_count, y, get_color(data, (int) x_text, \
			(int) y_text, ray_angle));
		y_text += step;
		y++;
		count++;
	}
	while (y < HEIGHT)
		my_pixel_put(&(data->img), rays_count, y++,
			rgb_to_hex(data->textures->floor));
}
