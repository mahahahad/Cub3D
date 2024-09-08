/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:04:39 by ryagoub           #+#    #+#             */
/*   Updated: 2024/09/07 19:51:26 by maabdull         ###   ########.fr       */
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
    float length;

    x_new = 0;
    y_new = 0;
	if (ray_angle > 180)
		y = floor(data->player->y / SQUARE) *( SQUARE)+ 64;
	else
		y = floor(data->player->y / SQUARE) *( SQUARE) - 1;
	x = data->player->x + (data->player->y - y) / tan(ray_angle * (PI / 180));
    while ( x >= 0 && x < WIDTH &&y >=0 && y < HEIGHT && data->map->grid[(int)(floor(y/ SQUARE))][(int)(floor((x / SQUARE)))] != '1')
    {
		if (ray_angle > 180)
			y_new = SQUARE;
		else
       		y_new = -SQUARE;
        x_new = SQUARE / tan(ray_angle * (PI / 180.0));
        y += y_new;
        x += x_new;
    }

    data->hx = x;
    data->hy = y;

    length = sqrt((data->player->x - x) * (data->player->x - x) + (data->player->y - y) * (data->player->y - y));
    return(floor(length));
}

float vertical_distance(float ray_angle, t_data *data)
{
	float x;
	float y;
	float x_new;
	float y_new;
	float length;

	x_new = 0;
	y_new = 0;
	if (ray_angle > 90 && ray_angle <= 270)
		x = floor(data ->player->x/SQUARE) * (SQUARE) - SQUARE;
	else
		x = floor(data ->player->x/SQUARE) * (SQUARE) + SQUARE;
	y = data ->player->y - ((data ->player->x - x) * tan(ray_angle* (PI / 180)));
	while ((y / SQUARE)>= 0&& (y / SQUARE) < data->map->rows && (x / SQUARE) >= 0 && (x / SQUARE) < (int)ft_strlen(data->map->grid[(int)(floor(y / SQUARE))]) && data->map->grid[(int)(floor(y / SQUARE))][(int)(floor((x / SQUARE)))] != '1')
	{
		if (ray_angle > 90 && ray_angle <= 270)
			x_new = -SQUARE;
		else
			x_new = SQUARE;
		y_new = SQUARE * tan(ray_angle* (PI / 180));
		y = y + y_new;
		x = x + x_new;
	}
	data -> vx= x;
	data ->vy =y;
	length = sqrt((data->player->x - x) * (data->player->x - x) + (data->player->y - y) * (data->player->y - y));
	return(floor(length));
}
void draw_ray(t_data *data,float ray_angle ,float ray_length )
{
	float i;
	float j;
	int count;

	count = 0;
	i = (data->player->x);
	j = (data->player->y);;
	while (i < WIDTH && j < HEIGHT && count < ray_length)
	{
		my_pixel_put(&(data->img), i, j, 0xFF8D85);
		i+=(cos(ray_angle * (PI / 180)));
		j-=(sin(ray_angle*(PI / 180)));
		count = sqrt((((int)ft_square((data->player->x ) - (i))))+ (((int)ft_square(data->player->y - (j)))));
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
	rays_count = 0;
	while (rays_count < WIDTH)
	{
		 if(vertical_distance(ray_angle, data)< horizontal_distance(ray_angle, data))
			 draw_ray(data, ray_angle,vertical_distance(ray_angle, data));
		else
			draw_ray(data, ray_angle,horizontal_distance(ray_angle, data));
		ray_angle = ray_angle + step_angle;
		rays_count++;
	}
	(void) ray_length;
}
