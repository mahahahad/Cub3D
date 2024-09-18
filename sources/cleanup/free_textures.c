/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 22:09:15 by maabdull          #+#    #+#             */
/*   Updated: 2024/09/18 22:43:22 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_textures(t_textures *textures)
{
	if (textures->north)
		free(textures->north);
	if (textures->east)
		free(textures->east);
	if (textures->west)
		free(textures->west);
	if (textures->south)
		free(textures->south);
	// if (textures->floor)
	// {
	// 	free(textures->floor[0]);
	// 	free(textures->floor[1]);
	// 	free(textures->floor[2]);
	// }
	// if (textures->ceiling)
	// {
	// 	free(textures->ceiling[0]);
	// 	free(textures->ceiling[1]);
	// 	free(textures->ceiling[2]);
	// }
}
