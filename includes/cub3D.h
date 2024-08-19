/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:51:19 by maabdull          #+#    #+#             */
/*   Updated: 2024/08/19 13:48:12 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* HEADER FILES */
# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include "utils.h"
# include "mlx.h"

/* DATA STRUCTURES */
typedef struct	s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
} t_data;

/* KEYCODES */
# ifdef __linux__
#  define KEY_ESC 65307
# else
#  define KEY_ESC 53
# endif

/* FUNCTION PROTOTYPES */
// ...

# endif
