/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryagoub <ryagoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:04:39 by ryagoub           #+#    #+#             */
/*   Updated: 2024/09/09 03:46:06 by ryagoub          ###   ########.fr       */
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
		y = floor(data->player->y / SQUARE) *( SQUARE) + SQUARE;
	else
		y = floor(data->player->y / SQUARE) *( SQUARE) - 0.0001;
	x = data->player->x + (data->player->y - y) / tan(ray_angle * (PI / 180));
   while ((y / SQUARE)>= 0&& (y / SQUARE) < data->map->rows && (x / SQUARE) >= 0 && (x / SQUARE) < (int)ft_strlen(data->map->grid[(int)(floor(y / SQUARE))])
	&& data->map->grid[(int)(floor(y / SQUARE))][(int)(floor((x / SQUARE)))] != '1')
    {
		if (ray_angle > 180 )
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
    data->hx = x;
    data->hy = y;
    length = sqrt((data->player->x - x) * (data->player->x - x) + (data->player->y - y) * (data->player->y - y));
    return(length);
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
		x = floor(data ->player->x / SQUARE) * (SQUARE) - 0.0001;
	else
		x = floor(data ->player->x / SQUARE) * (SQUARE) + SQUARE;
	y = data ->player->y + ((data ->player->x - x) * tan(ray_angle* (PI / 180)));
	while ((y / (float) SQUARE) >= 0 && (y / (float) SQUARE) <(float) data->map->rows && (x / (float) SQUARE) >= 0 && (x / (float) SQUARE)
	 < (int)ft_strlen(data->map->grid[((int)(y / (float) SQUARE))])
	&& data->map->grid[(int)((y / (float) SQUARE))][(int)(((x / (float) SQUARE)))] != '1')
	{
		if (ray_angle > 90 && ray_angle <= 270)
			x_new = -SQUARE;
		else
			x_new = SQUARE;
		y_new = (float) SQUARE * tan(ray_angle* (PI / 180));
		if ((ray_angle > 0 && ray_angle < 90) || (ray_angle > 270 && ray_angle <= 360))
			y -=  y_new;
		else
			y +=  y_new;
		x += x_new;
	}
	data -> vx= x;
	data ->vy = y;
	length = sqrt((data->player->x - x) * (data->player->x - x) + (data->player->y - y) * (data->player->y - y));
	return(length);
}

float wall_length(t_data *data, float ray_length, float ray_angle)
{
	float ppd;
	float wall_length;

	ray_length = ray_length * cos((ray_angle - data->player->angle)* (PI / 180));
	ppd = (WIDTH / 2 ) / tan(30 * (PI / 180));
	wall_length = ceil((SQUARE / ray_length) * ppd);
	if(wall_length > HEIGHT)
		wall_length = HEIGHT - 2;
	printf("%f wall length = \n",wall_length);
	printf("%f ray length = \n",ray_length);
	return(wall_length);
}
void draw_wall(t_data *data,float wall_length,int rays_count, int flag)
{
	float length;
	float count;
	float x;
	float y;

	length = wall_length;
	count = 0;
	x = rays_count;
	y = (HEIGHT/ 2) - (wall_length /2);
	while (count < wall_length && x < WIDTH && y < HEIGHT && x > 0 && y > 0)
	{
		if (flag == 0)
			my_pixel_put(&(data->img), x, y , 0x990000);
		else
			my_pixel_put(&(data->img), x, y , 0x99FF99);
		y++;
		count++;
	}
}


void draw_ray(t_data *data,float ray_angle ,float ray_length)
{
	float i;
	float j;
	float count;

	count = 0;
	i = (data->player->x);
	j = (data->player->y);
	while (j > 0 && i > 0 && j /(float )SQUARE < data->map->rows
		&& i / (float)SQUARE  < (int)ft_strlen(data->map->grid[(int)j/ SQUARE ])
		&& count <= ray_length)
	{
		my_pixel_put(&(data->img), i, j, 0xFF8D85);
		i+=(cos(ray_angle * (PI / 180)));
		j-=(sin(ray_angle*(PI / 180)));
		 count = sqrt((data->player->x - i) * (data->player->x - i) + (data->player->y - j) * (data->player->y - j));
	}
}

void raycast(t_data *data)
{
	float step_angle;
	float ray_length;
	float ray_angle;
	int rays_count;


	ray_angle = data->player->angle + 30;
	  if (ray_angle < 0) {
       ray_angle += 2 * 180;
    }
   if(ray_angle >= (2 * 180)) {
        ray_angle -= 2 * 180;
    }
	ray_length = 0;
	step_angle = 60 /(float) WIDTH;
	rays_count = 0;
	int i;
	i = 0;
	while (rays_count < WIDTH)
	{
		if(vertical_distance(ray_angle, data)< horizontal_distance(ray_angle, data))
		{
			draw_ray(data, ray_angle,vertical_distance(ray_angle, data));
			draw_wall(data,wall_length(data, vertical_distance(ray_angle, data), ray_angle), rays_count,0);
		}
		else
		{
			draw_ray(data, ray_angle,horizontal_distance(ray_angle, data));
			draw_wall(data,wall_length(data, horizontal_distance(ray_angle, data), ray_angle), rays_count, 1);
		}
		ray_angle = ray_angle - step_angle;
		if (roundf(ray_angle) <= 0)
			ray_angle = 360;
		rays_count++;
		i++;
	}
}
