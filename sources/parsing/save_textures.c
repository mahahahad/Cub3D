/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:10:24 by maabdull          #+#    #+#             */
/*   Updated: 2024/09/28 18:02:28 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	save_north_texture(t_data *data)
{
	data->nh = 0;
	data->nw = 0;
	data->north.img = mlx_xpm_file_to_image(data->mlx_ptr, \
		data->textures->north, &(data->nw), &(data->nh));
	data->north.img_pixels_ptr = (int *) mlx_get_data_addr(data->north.img, \
		&(data->north.bits_per_pixel), &(data->north.line_len), \
		&(data->north.endian));
	if (!data->north.img || !data->north.img_pixels_ptr)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	save_east_texture(t_data *data)
{
	data->eh = 0;
	data->ew = 0;
	data->east.img = mlx_xpm_file_to_image(data->mlx_ptr, \
		data->textures->east, &(data->ew), &(data->eh));
	data->east.img_pixels_ptr = (int *) mlx_get_data_addr(data->east.img, \
		&(data->east.bits_per_pixel), &(data->east.line_len), \
		&(data->east.endian));
	if (!data->east.img || !data->east.img_pixels_ptr)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	save_west_texture(t_data *data)
{
	data->wh = 0;
	data->ww = 0;
	data->west.img = mlx_xpm_file_to_image(data->mlx_ptr, \
		data->textures->west, &(data->ww), &(data->wh));
	data->west.img_pixels_ptr = (int *) mlx_get_data_addr(data->west.img, \
		&(data->west.bits_per_pixel), &(data->west.line_len), \
		&(data->west.endian));
	if (!data->west.img || !data->west.img_pixels_ptr)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	save_south_texture(t_data *data)
{
	data->sh = 0;
	data->sw = 0;
	data->south.img = mlx_xpm_file_to_image(data->mlx_ptr, \
		data->textures->south, &(data->sw), &(data->sh));
	data->south.img_pixels_ptr = (int *) mlx_get_data_addr(data->south.img, \
		&(data->south.bits_per_pixel), &(data->south.line_len), \
		&(data->south.endian));
	if (!data->south.img || !data->south.img_pixels_ptr)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	save_images(t_data *data)
{
	if (save_north_texture(data) == EXIT_FAILURE)
		return (ft_err("Could not save North texture."));
	if (save_east_texture(data) == EXIT_FAILURE)
		return (ft_err("Could not save East texture."));
	if (save_west_texture(data) == EXIT_FAILURE)
		return (ft_err("Could not save West texture."));
	if (save_south_texture(data) == EXIT_FAILURE)
		return (ft_err("Could not save South texture."));
	return (EXIT_SUCCESS);
}
