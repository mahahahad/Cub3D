/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:24:17 by maabdull          #+#    #+#             */
/*   Updated: 2024/08/21 22:40:38 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * @brief Append the provided string `str` to the provided table `tab`
 * 
 * Frees the previous table `tab` and returns a newly allocated one with the
 * appended string.
 * 
 * @param tab 
 * @param str 
 * @return char** 
 */
char	**ft_tabjoin(char **tab, char *str)
{
	int		rows;
	int		i;
	char	**new_tab;

	new_tab = NULL;
	if (!tab)
	{
		new_tab = malloc(sizeof(char *) * 2);
		new_tab[0] = ft_strdup(str);
		new_tab[1] = NULL;
		return (new_tab);
	}
	rows = 0;
	i = -1;
	while (tab[rows])
		rows++;
	new_tab = malloc(sizeof(char *) * (rows + 2));
	while (++i < rows)
		new_tab[i] = ft_strdup(tab[i]);
	new_tab[i++] = ft_strdup(str);
	new_tab[i] = NULL;
	ft_freetab(tab);
	return (new_tab);
}
