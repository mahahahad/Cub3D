/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:00:33 by maabdull          #+#    #+#             */
/*   Updated: 2024/08/19 20:06:16 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	is_in_str(const char *str, const char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (1);
	return (0);
}

/// @brief
	// Removes the characters in the string 'set' from the start and end of
	// string 's1'
/// @param s1
	// The string to trim
/// @param set
	// The characters to trim
/// @return
	// The trimmed string
char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*final_str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (is_in_str(set, s1[start]))
		start++;
	if (start > end)
		return (ft_strdup(s1 + end + 1));
	while (is_in_str(set, s1[end]) && end)
		end--;
	final_str = ft_substr(s1, start, end - start + 1);
	if (!final_str)
		return (NULL);
	return (final_str);
}
