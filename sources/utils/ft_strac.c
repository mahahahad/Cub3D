/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strac.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:32:26 by maabdull          #+#    #+#             */
/*   Updated: 2024/08/21 17:28:42 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * @brief Append a character to the provided `str`
 * 
 * Frees the `str` variable and returns a newly malloced str with the char `c`
 * appended to it.
 * 
 * @param str 
 * @param c 
 * @return char* 
 */
char	*ft_strac(char *str, char c)
{
	char	*new_str;
	int		i;
	char	append_char[2];

	append_char[0] = c;
	append_char[1] = '\0';
	if (!str)
		return (ft_strdup(append_char));
	new_str = malloc(ft_strlen(str) + 2);
	i = -1;
	while (str[++i])
		new_str[i] = str[i];
	new_str[i++] = c;
	new_str[i] = '\0';
	free(str);
	str = new_str;
	return (new_str);
}
