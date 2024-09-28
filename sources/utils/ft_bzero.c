/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:57:41 by maabdull          #+#    #+#             */
/*   Updated: 2024/08/26 16:13:45 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/// @brief
	// Fills 'n' bytes of 's' with the 0 character
	// Like memset but with 0 instead of a specific user provided character
/// @param s
	// The string to replace
/// @param n
	// The number of characters to replace
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *) s;
	i = 0;
	if (n)
		while (i != n)
			str[i++] = '\0';
}
