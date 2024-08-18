/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:51:17 by maabdull          #+#    #+#             */
/*   Updated: 2024/08/18 23:20:44 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	int	map_fd;
	char	*line, *buffer, *temp;

	if (argc != 2)
		return (ft_putendl_fd("Please enter a map file", 2), 1);
	map_fd = open(argv[1], O_RDONLY);
	buffer = malloc(1);
	while (true)
	{
		line = get_next_line(map_fd);
		if (!line)
			break ;
		temp = buffer;
		buffer = ft_strjoin(buffer, line);
		free(line);
		free(temp);
	}
	ft_putendl_fd(buffer, 1);
	free(buffer);
	return (0);
}
