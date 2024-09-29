/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 22:10:26 by maabdull          #+#    #+#             */
/*   Updated: 2024/09/29 22:11:11 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_texture_extension(char *texture)
{
	int		texture_len;
	char	*texture_ext;

	texture_len = ft_strlen(texture);
	if (texture_len <= 4)
		return (EXIT_FAILURE);
	texture_ext = ft_substr(texture, texture_len - 4, 4);
	if (ft_strncmp(texture_ext, ".xpm", 4))
		return (free(texture_ext), EXIT_FAILURE);
	return (free(texture_ext), EXIT_SUCCESS);
}

int	check_texture_extensions(t_data *data)
{
	if (check_texture_extension(data->textures->north) == EXIT_FAILURE)
		return (ft_err("North texture is not an xpm file."));
	if (check_texture_extension(data->textures->east) == EXIT_FAILURE)
		return (ft_err("East texture is not an xpm file."));
	if (check_texture_extension(data->textures->west) == EXIT_FAILURE)
		return (ft_err("West texture is not an xpm file."));
	if (check_texture_extension(data->textures->south) == EXIT_FAILURE)
		return (ft_err("South texture is not an xpm file."));
	return (EXIT_SUCCESS);
}
