/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:58:53 by maabdull          #+#    #+#             */
/*   Updated: 2024/09/04 14:31:18 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

# define PROJECTION_WIDTH 120

void	fill_image_with_color(void *mlx, void *image, t_coords points[2], \
	int color)
{
	int pixel_bits;
	int line_bytes;
	int endian;
	char *buffer;

	buffer = mlx_get_data_addr(image, &pixel_bits, &line_bytes, &endian);
	if (pixel_bits != 32)
		color = mlx_get_color_value(mlx, color);
	// while (y < (int) size.y)
	// {
	// 	x = 0;
	// 	while (x < (int) size.x)
	// 	{
	// printf("Window width: %f\nWindow height: %f\n", size->x, size->y);
	for(int y = points[0].y; y < points[1].y; ++y)
	for(int x = points[0].x; x <= points[1].x; ++x)
	{
		int pixel = (y * line_bytes) + (x * 4);

		if (endian == 1)        // Most significant (Alpha) byte first
		{
			buffer[pixel + 0] = (color >> 24);
			buffer[pixel + 1] = (color >> 16) & 0xFF;
			buffer[pixel + 2] = (color >> 8) & 0xFF;
			buffer[pixel + 3] = (color) & 0xFF;
		}
		else if (endian == 0)   // Least significant (Blue) byte first
		{
			buffer[pixel + 0] = (color) & 0xFF;
			buffer[pixel + 1] = (color >> 8) & 0xFF;
			buffer[pixel + 2] = (color >> 16) & 0xFF;
			buffer[pixel + 3] = (color >> 24);
		}
	}
}

typedef struct s_ray
{
	bool	is_at_wall;
	double	length;
	double	rotation;
	int		x_step;
	int		y_step;
	t_coords	current_pos;
} t_ray;

/**
 * Ensure the following variables are set:
 * 	- Player starting location
 * 	- Ray rotation (and axis step values) 
 * Calculate, using trigonometry, the distance to each axis' intersection point
 * Compare the values and move to the shortest one
 * Check if that tile is a wall
 * If it isn't, move to that tile and repeat the process
 */

double	get_stripe_height(t_data *data, int stripe_index)
{
	int		i;
	t_ray	ray;
	t_coords	player_pos;
	t_coords	step;

	(void) data;
	i = 0;
	ray.length = 0.0; //* Will change
	ray.is_at_wall = false; //* Will change
	player_pos.x = data->player->position.x;
	player_pos.y = data->player->position.y;
	ray.current_pos = player_pos; //* Will change
	ray.rotation = -33 + 66 * stripe_index / WINDOW_WIDTH;
	if (ray.rotation < 0 && ray.rotation > -90)
	{
		step.x = -1;
		step.y = -1;
	}
	if (ray.rotation > 0 && ray.rotation < 90)
	{
		step.x = 1;
		step.y = -1;
	}
	int	total_angle = 90;
	if (step.x < 0)
		total_angle *= -1;
	// Keep checking for walls until either a wall is found or 30 iterations
	// have occured.
	while (!ray.is_at_wall && i < 30)
	{
		// Get the distance to the nearest x intersection with 1 y step
		double y_hypo = 1 / cos(ray.rotation * (M_PI / 180));
		// Get the distance to the nearest y intersection with 1 x step
		double x_hypo = 1 / cos((total_angle - ray.rotation) * (M_PI / 180));
		if (y_hypo < x_hypo)
		{
			ray.current_pos.y += step.y;
			ray.length += y_hypo;
		}
		else
		{
			ray.current_pos.x += step.x;
			ray.length += x_hypo;
		}
		if (data->map->grid[ray.current_pos.y][ray.current_pos.x] == '1')
			ray.is_at_wall = true;
		i++;
	}
	return (ray.length);
}

typedef struct s_stripe
{
	int	color;
	t_vec2	size;
}	t_stripe;

// Cast a ray for each column of pixels in the projection plane
// The reason for doing this is to obtain a distance to the nearest collision 
// for each ray which can then be used to render walls where the further they 
// are, the shorter they will be
int	cast_rays(t_data *data)
{
	void	*image;
	int	i = 0;
	// t_stripe	stripe;
	t_vec2	size;
	t_coords	points[2];

	size.x = WINDOW_WIDTH;
	size.y = WINDOW_HEIGHT;
	// Create an image
	image = mlx_new_image(data->mlx_ptr, size.x, size.y);
	// Loop through the windows width and for each stripe:
	while (i < size.x)
	{
		// Get its height
		points[0].x = i;
		points[0].y = 0;
		points[1].y = get_stripe_height(data, i);
		points[1].x = i;
		// Fill the relevant pixels in the full image
		fill_image_with_color(data->mlx_ptr, image, points, 0x00FF00);
		i++;
		// printf("%d %d\n", points[1].y, i);
	}
	// Display the image
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, image, 0, 0);
	// Delete the image
	mlx_destroy_image(data->mlx_ptr, image);
	return (0);
}
