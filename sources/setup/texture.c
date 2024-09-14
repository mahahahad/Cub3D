/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryagoub <ryagoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:18:16 by ryagoub           #+#    #+#             */
/*   Updated: 2024/09/14 05:25:41 by ryagoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
// x and y are the coordinates in the wall i have to find the corresponding
//  x and y pixel in the texture but as we know in the texture the image is not
// have the same format as the wall so we have to find the offset i mean the image is contain of bits and each group is a single pixel
// so the issue is i have to find the row first and then the bits that made up the pixel
// void get_color_x(t_data *data,float x, float y)
// {

// }
void  save_images(t_data *data)
{
	data ->nh = 0;
	data -> nw = 0;
	data->north = malloc(sizeof(t_img));
	data->south = malloc(sizeof(t_img));
	data->west = malloc(sizeof(t_img));
	data->east = malloc(sizeof(t_img));
	data ->north->img = mlx_xpm_file_to_image(data->mlx_ptr, "textures/goodboy.xpm",&(data->nw),&(data->nh));
	data->north->img_pixels_ptr = mlx_get_data_addr(data->north->img,&(data->north->bits_per_pixel),&(data->north->line_len),&(data->north->endian));

	data ->sh = 0;
	data -> sw = 0;
	data ->south->img = mlx_xpm_file_to_image(data->mlx_ptr, "textures/goodboy.xpm",&(data->nw),&(data->nh));
	data ->eh = 0;
	data -> ew = 0;
	data ->east->img = mlx_xpm_file_to_image(data->mlx_ptr, "textures/goodboy.xpm",&(data->nw),&(data->nh));
	data ->wh = 0;
	data -> ww = 0;
	data ->west->img = mlx_xpm_file_to_image(data->mlx_ptr, "textures/goodboy.xpm",&(data->nw),&(data->nh));
}
t_img *get_image(t_data *data,float ray_angle)
{
	if (ray_angle > 180)
		return(data->south);
	if (ray_angle < 180)
		return(data->north);
	return(0);
}

int get_x(t_data *data , int flag,float ray_angle, float ray_length)
{
	float x_text;
	float end_point;
	// printf ("%f ray angle is \n",ray_angle);

	if (flag == 0)
	{
		// end_point = data->hx - cos(ray_angle * (PI/ 180));
		end_point = data->player->x  + (ray_length *cos(ray_angle * (PI/ 180)));
		// printf("from within function x_pos -> %f\n", end_point);
		// printf("%f end point \n",end_point);
	}
	if(flag == 1)
	{
			end_point = data->player->y  - (ray_length * sin(ray_angle * (PI/ 180)))  ;

			// end_point =data->vy - sin(ray_angle * (PI/ 180));
	}
	end_point -= floor(end_point);
	// printf("end points are %f\n", end_point);
	x_text = (end_point * (float)Texture);
	return( x_text);
}
int get_color(t_data *data , int x, int y, float ray_angle)
{
	int pixel_index;
	t_img *image;
	int *image_in_pixs;
	pixel_index = 0;
	image = get_image(data,ray_angle);
	if (image == NULL )
    	return (printf("im here the image is null\n"),0);
	// image_in_pixs = (int *)mlx_get_data_addr(image->img,&(image->bits_per_pixel),&(image->line_len),&(image->endian));
	image_in_pixs = (int *) image->img_pixels_ptr;
	int color = *(image_in_pixs + (Texture * y + x));
	// printf("x = %d and y = %d\n", x, Texture * y);
	// printf("(%d,%d),(x_text,y_text) -> color %ld\n", x, y, color);
	return(color);
}

// flag = 0 x won
// flaf = 1 y won

void draw_image(t_data *data,float wall_length,int rays_count, int flag, float ray_angle, float ray_length)
{
	flag = 0;
	// float length;
	float count;
	float x;
	float y;
	float step;
	float textpos;
	int y_text;
	int x_text;
	step =  (float) Texture / wall_length;
	// length = wall_length;
	count = 0;
	x = rays_count;
	// ray_length = 0;
	y = (HEIGHT/ 2) - (wall_length /2);
	textpos =(y - (HEIGHT/2) + (wall_length /2) )* step;
	// printf("%f textpos \n",textpos);
	while (count < wall_length /*&& x < WIDTH && y < HEIGHT && x >= 0 && y >= 0*/)
	{
		x_text = get_x(data , flag,ray_angle, ray_length);
		y_text = (int) textpos & (Texture - 1);
		// // printf("ytext-> %d\n", y_text);
		textpos += step;
		// printf("from outseide function x_pos -> %f\n", data->hx);
		my_pixel_put(&(data->img), x, y , get_color(data ,  x_text,y_text,ray_angle));
		y++;
		count++;
	}
}
