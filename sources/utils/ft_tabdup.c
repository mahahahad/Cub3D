/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:23:55 by maabdull          #+#    #+#             */
/*   Updated: 2024/08/21 22:40:24 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static char	check_char(char c)
{
	char	zero;

	zero = '0';
	if (ft_strchr(WHITESPACE, c))
		return (c);
	return (zero);
}

/**
 * @brief Duplicate the provided table `tab` using `fill_char` as the 
 * character instead of the one in the table to duplicate.
 * 
 * if `fill_char` is '\0', characters from the original table are used.
 * 
 * @param tab 
 * @param fill_char 
 * @return char** 
 */
char	**ft_tabdup(char **tab, char fill_char)
{
	int		y;
	int		x;
	char	**duped_tab;
	char	*line;

	y = 0;
	duped_tab = NULL;
	line = NULL;
	while (tab[y])
	{
		x = -1;
		while (tab[y][++x])
		{
			if (!fill_char)
				line = ft_strac(line, tab[y][x]);
			else
				line = ft_strac(line, check_char(tab[y][x]));
		}
		duped_tab = ft_tabjoin(duped_tab, line);
		free(line);
		line = NULL;
		y++;
	}
	return (duped_tab);
}
