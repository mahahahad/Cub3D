/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:13:21 by maabdull          #+#    #+#             */
/*   Updated: 2024/09/18 22:41:15 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_isspace(const char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

static int	ft_issign(const char c)
{
	return (c == '+' || c == '-');
}

/// @brief
// Converts a number stored as a string to an integer type
/// @param str
// The number as a string to be converted to an integer type
/// @return
// The converted integer
int	ft_atoi(const char *str)
{
	int	num;
	int	sign;

	num = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		sign = -1;
	if (ft_issign(*str))
		str++;
	while (*str)
	{
		if (ft_isdigit(*str))
			num = (num * 10) + *(str++) - '0';
		else
			break ;
	}
	return (sign * num);
}
