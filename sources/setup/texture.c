/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryagoub <ryagoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:18:16 by ryagoub           #+#    #+#             */
/*   Updated: 2024/09/15 11:08:22 by ryagoub          ###   ########.fr       */
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
	// data->north = malloc(sizeof(t_img));
	// data->south = malloc(sizeof(t_img));
	// data->west = malloc(sizeof(t_img));
	// data->east = malloc(sizeof(t_img));
	data ->north.img = mlx_xpm_file_to_image(data->mlx_ptr, "textures/goodboy.xpm",&(data->nw),&(data->nh));
	data->north.img_pixels_ptr = (int *)mlx_get_data_addr(data->north.img,&(data->north.bits_per_pixel),&(data->north.line_len),&(data->north.endian));

	data ->sh = 0;
	data -> sw = 0;
	data ->south.img = mlx_xpm_file_to_image(data->mlx_ptr, "textures/goodboy.xpm",&(data->nw),&(data->nh));
	data ->eh = 0;
	data -> ew = 0;
	data ->east.img = mlx_xpm_file_to_image(data->mlx_ptr, "textures/goodboy.xpm",&(data->nw),&(data->nh));
	data ->wh = 0;
	data -> ww = 0;
	data ->west.img = mlx_xpm_file_to_image(data->mlx_ptr, "textures/goodboy.xpm",&(data->nw),&(data->nh));
}
t_img get_image(t_data *data,float ray_angle)
{
	if (ray_angle > 180)
		return(data->north);
	// if (ray_angle < 180)
	return(data->north);
	// return();
}
float get_x(t_data *data , int flag,float ray_angle, float ray_length)
{
	// ray_angle =0;
	ray_length = 0;
	float x_text;

	if (flag == 0)
	{
		x_text =  (int)((data ->hx))%Texture ;
		if (ray_angle > 180)
			x_text= 31 - x_text;
	}
	if(flag == 1)
	{
		x_text =  (int)(data ->vy )%Texture;
		if(ray_angle > 90 && ray_angle < 270)
			x_text= 31 - x_text;
	}
	return( x_text);
}

// float get_x(t_data *data , int flag,float ray_angle, float ray_length)
// {
// 	// ray_angle =0;
// 	ray_length = 0;
// 	float x_text;

// 	if (flag == 0)
// 	{
// 		x_text =  (int)((data ->hx) /2.0)%Texture ;
// 		if (ray_angle > 180)
// 			x_text= 31 - x_text;
// 	}
// 	if(flag == 1)
// 	{
// 		x_text =  (int)(data ->vy /2.0)%Texture;
// 		if(ray_angle > 90 && ray_angle < 270)
// 			x_text= 31 - x_text;
// 	}
// 	return( x_text);
// }

int get_color(t_data *data , int x, int y, float ray_angle)
{
	t_img image;
	int *image_in_pixs;
	image = get_image(data,ray_angle);
	image_in_pixs =  image.img_pixels_ptr;
	int color = 0;
	int offset = ((y * (data->north.line_len/4)) + x);
	printf("line length is %d\n",data->north.line_len);
	color = *(image_in_pixs + offset );
	return(color);
}

// flag = 0 x won
// flaf = 1 y won

void draw_image(t_data *data,int wall_length,int rays_count, int flag, float ray_angle, float ray_length)
{
	int count;
	int x;
	int y;
	float step;
	float y_text;
	float x_text;
	step = ((1.0 * Texture) / wall_length);
	// printf(" the wall length is %d\n",wall_length);
	int ty_off=0;
	if ((int)wall_length >  HEIGHT)
	{ty_off = ((int)wall_length - HEIGHT)/2.0;
	wall_length = HEIGHT;}


	count = 0;
	x = rays_count;
	y = (HEIGHT/ 2) - ((int)wall_length /2);
	y_text= ty_off * step;
	while (count <(int) wall_length && x < WIDTH && y < HEIGHT && x >= 0 && y >= 0)
	{
		x_text = get_x(data , flag,ray_angle, ray_length);
		y_text += step;
		my_pixel_put(&(data->img),x, y , get_color(data , (int) x_text,(int)y_text,ray_angle));
		y++;
		count++;
	}
}

