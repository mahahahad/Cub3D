/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryagoub <ryagoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:01:22 by ryagoub           #+#    #+#             */
/*   Updated: 2024/09/28 16:48:36 by ryagoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	int	offset;

	if (y < 0 || y >= HEIGHT || x < 0 || x >= WIDTH)
		return ;
	offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));
	img->img_pixels_ptr[offset / 4] = color;
}

int	rgb_to_hex(int rgb[3])
{
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}
