/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 22:02:08 by maabdull          #+#    #+#             */
/*   Updated: 2024/09/29 22:12:32 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	create_minimap_image(t_data *data)
{
	data->minimap.img = mlx_new_image(data->mlx_ptr, (data->map->max_cols + 1) \
		* GRID_PIX_SIZE, data->map->rows * GRID_PIX_SIZE);
	if (data->minimap.img == NULL)
		return (ft_err("Image could not be created"));
	data->minimap.img_pixels_ptr = (int *)(mlx_get_data_addr(data->minimap.img,
				&(data->minimap.bits_per_pixel),
				&(data->minimap.line_len),
				&(data->minimap.endian)));
	return (EXIT_SUCCESS);
}

int	create_render_image(t_data *data)
{
	data->img.img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (data->img.img == NULL)
		return (ft_err("Image could not be created"));
	data->img.img_pixels_ptr = (int *)(mlx_get_data_addr(data->img.img,
				&(data->img.bits_per_pixel),
				&(data->img.line_len),
				&(data->img.endian)));
	return (EXIT_SUCCESS);
}

int	init_images(t_data *data)
{
	if (create_render_image(data) == EXIT_FAILURE \
		|| create_minimap_image(data) == EXIT_FAILURE \
		|| save_images(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
