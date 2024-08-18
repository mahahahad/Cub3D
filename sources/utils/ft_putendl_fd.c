/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:44:19 by maabdull          #+#    #+#             */
/*   Updated: 2024/08/18 19:06:42 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/// @brief
	// Write the string 's' to the file descriptor 'fd' with a newline at the
	// end
/// @param s
	// The string to display
/// @param fd
	// The file descriptor to write to
void	ft_putendl_fd(const char *s, int fd)
{
	int	i;

	i = -1;
	if (s)
		while (s[++i])
			write(fd, &s[i], 1);
	write(fd, "\n", 1);
}
