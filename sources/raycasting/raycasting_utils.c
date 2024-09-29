/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:29:44 by ryagoub           #+#    #+#             */
/*   Updated: 2024/09/29 19:07:33 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_all(t_data *data, float x, float y)
{
	if ((y / (float) SQUARE) >= 0 \
		&& (y / (float) SQUARE) < (float) data->map->rows \
		&& (x / (float) SQUARE) >= 0 \
		&& (x / (float) SQUARE) \
			< (int) ft_strlen(data->map->grid[((int)(y / (float) SQUARE))]) \
		&& data->map->grid[(int)((y / (float) SQUARE))][\
			(int)(((x / (float) SQUARE)))] != '1')
		return (0);
	return (1);
}

inline float	cal_length(t_data *data, float x, float y)
{
	return (sqrt(pow(data->player->x - x, 2) + pow(data->player->y - y, 2)));
}
