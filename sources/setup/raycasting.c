/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryagoub <ryagoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:04:39 by ryagoub           #+#    #+#             */
/*   Updated: 2024/09/05 12:12:07 by ryagoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float ft_square(float num)
{
	return(num * num);
}
// the player is facing up -> fix it later
float horizontal_distance(float ray_angle, t_data *data)
{
	float x;
	float y;
	float x_new;
	float y_new;
	int first_x;
	int first_y;
	float length;

	x_new = 0;
	y_new = 0;
	y = floor(data ->player->y/SQUARE) * (SQUARE) - 1;

	x = data ->player->x + ((data ->player->y - y) / tan(ray_angle* (PI / 180)));
	first_x = x;
	first_y = y;
	while (x < WIDTH && y < HEIGHT && data->map->grid[(int)(floor(y/ SQUARE))][(int)(floor((x / SQUARE)))] != '1')
	{
		y_new = - SQUARE;
		x_new = SQUARE / tan(ray_angle* (PI / 180));
		y = y + y_new;
		x = x+ x_new;
	}
	// data -> hx= x;
	// data ->hy =y;
	length = sqrt((((int)ft_square(first_x - (x))))+ (((int)ft_square(first_y - (y)))));
	return(floor(length));
}
float vertical_distance(float ray_angle, t_data *data)
{
	float x;
	float y;
	float x_new;
	float y_new;
	int first_x;
	int first_y;
	float length;

	x_new = 0;
	y_new = 0;
	x = floor(data ->player->x/SQUARE) * (SQUARE) + SQUARE;
	y = data ->player->y - ((data ->player->x - x) * tan(ray_angle* (PI / 180)));
	first_x = x;
	first_y = y;

	while ((y / SQUARE) < data->map->rows && (x / SQUARE) < (int)ft_strlen(data->map->grid[(int)(floor(y / SQUARE))]) && data->map->grid[(int)(floor(y / SQUARE))][(int)(floor((x / SQUARE)))] != '1')
	{
		x_new = SQUARE;
		y_new = SQUARE * tan(ray_angle* (PI / 180));
		y = y + y_new;
		x = x + x_new;
	}
	// data -> vx= x;
	// data ->vy =y;
	length = sqrt((((int)ft_square(first_x - (x))))+ (((int)ft_square(first_y - (y)))));
	return(floor(length));
}
void draw_ray(t_data *data,float ray_angle ,float ray_length )
{
	float i;
	float j;
	int count;

	count = 0;
	i = (data->player->x );
	j = (data->player->y);
	i = i + (cos(ray_angle * (PI / 180)));
	j = j + (sin(ray_angle*(PI / 180)));
	while (count < ray_length)
	{
		// mlx_pixel_put(data->mlx_ptr, data->win_ptr,i , j,0xFF8D85 );
		my_pixel_put(&(data->img), i, j, 0xFF8D85);
		i+=(cos(ray_angle * (PI / 180)));
		j-=(sin(ray_angle*(PI / 180)));
		count = sqrt((((int)ft_square((data->player->x ) - (i))))+ (((int)ft_square(data->player->y - (j)))));;
	}
}

float length_of_ray(t_data *data, float ray_angle)
{
	float xdist;
	// float ydist;

	xdist = horizontal_distance(ray_angle,data);
	// ydist = vertical_distance(ray_angle, data);
	// printf("this is xdist%f\n this is ydist%f\n", xdist, ydist);
	// if (xdist < ydist)
		return(xdist);
	// return(ydist);
}


void raycast(t_data *data)
{
	float step_angle;
	float ray_length;
	float ray_angle;
	int rays_count;

	ray_angle = data->player->angle - 30;
	ray_length = 0;
	step_angle = 60 /(float) WIDTH;
	// printf ("%f this is step angle\n",step_angle);
	rays_count = 0;
	int i = 0;
	// while (rays_count < (float) WIDTH)
	while (ray_angle <= data->player->angle)
	{
		ray_length = length_of_ray(data ,ray_angle);
		// ray_length = length_of_ray(data ,ray_angle) - (data->player->x % SQUARE);
		 if(vertical_distance(ray_angle, data)< horizontal_distance(ray_angle, data))
			 draw_ray(data, ray_angle,vertical_distance(ray_angle, data));
		else
			draw_ray(data, ray_angle,horizontal_distance(ray_angle, data));
		printf("length -> %f\n", ray_length);
		draw_ray(data, ray_angle, ray_length);
		// ray_angle = ray_angle + step_angle;
		ray_angle += 0.5;
		rays_count++;
		i++;
		if (i == 1)
			break ;
	}
}
