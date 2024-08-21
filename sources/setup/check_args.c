/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 22:19:37 by maabdull          #+#    #+#             */
/*   Updated: 2024/08/21 22:54:36 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_valid_ext(char *file_name)
{
	int		len;
	char	*ext;

	len = ft_strlen(file_name);
	if (len <= 4)
		return (EXIT_FAILURE);
	ext = ft_substr(file_name, len - 4, 4);
	if (ft_strncmp(ext, ".cub", 4))
		return (free(ext), EXIT_FAILURE);
	return (free(ext), EXIT_SUCCESS);
}

int	are_args_valid(int argc, char **argv)
{
	if (argc != 2)
		return (ft_err("Please enter a map file."));
	if (is_valid_ext(argv[1]) == EXIT_FAILURE)
		return (ft_err("Please enter a .cub map file"));
	return (EXIT_SUCCESS);
}
