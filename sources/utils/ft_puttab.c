/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 23:51:11 by maabdull          #+#    #+#             */
/*   Updated: 2024/08/21 12:21:18 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * @brief Print a 2D array in a readable format.
 * 
 * @param arr 
 */
void	ft_puttab(char **arr)
{
	int	x;
	int	y;

	y = 0;
	while (arr[y])
	{
		x = 0;
		write(1, "[", 1);
		while (arr[y][x])
		{
			write(1, &arr[y][x], 1);
			if (arr[y][x + 1])
				write(1, ", ", 2);
			x++;
		}
		write(1, "]\n", 2);
		y++;
	}
}
