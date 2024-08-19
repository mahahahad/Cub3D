/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:51:19 by maabdull          #+#    #+#             */
/*   Updated: 2024/08/19 23:57:10 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ************ *
 * HEADER FILES *
 * ************ */

# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include "utils.h"
# include "mlx.h"

/* *************** *
 * DATA STRUCTURES *
 * *************** */

typedef struct	s_map
{
	int		fd;
	char	*full;
	char	**content;
}	t_map;

typedef struct s_textures
{
	char	*north;
	char	*east;
	char	*west;
	char	*south;
	char	*floor;
	char	*ceiling;
}	t_textures;

typedef struct	s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_map		*map;
	t_textures *textures;
}	t_data;

typedef enum	e_texture_types
{
	NORTH,
	EAST,
	WEST,
	SOUTH,
	FLOOR,
	CEILING
}	t_texture_type;

/* ******** *
 * KEYCODES *
 * ******** */

# ifdef __linux__
#  define KEY_ESC 65307
# else
#  define KEY_ESC 53
# endif

/* ************* *
 * MISCELLANEOUS *
 * ************* */

# define WHITESPACE " \t\n\v\r"

/* ******************* *
 * FUNCTION PROTOTYPES *
 * ******************* */
// ...

# endif
