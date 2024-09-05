/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryagoub <ryagoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:51:19 by maabdull          #+#    #+#             */
/*   Updated: 2024/09/05 13:28:37 by ryagoub          ###   ########.fr       */
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
# include <math.h>
#include <stdio.h>

# define SQUARE 30
# define SPEED 5
# define PI 3.14159265359
# define WIDTH 1800
# define HEIGHT 1200

/* *************** *
 * DATA STRUCTURES *
 * *************** */

typedef struct s_map
{
	int		fd;
	int		rows;
	char	*full;
	char	**grid;
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



typedef struct s_player
{
	char	direction;
	int		angle;
	int		x;
	int		y;
}	t_player;

typedef struct s_coords
{
	int	x;
	int	y;
}	t_coords;

typedef struct s_img {
	void	*img;
	char	*img_pixels_ptr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}				t_img;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_map		*map;
	t_textures	*textures;
	t_player	*player;
	float		hx;
	float		hy;
	float		vx;
	float		vy;
}	t_data;

typedef enum e_texture_types
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

// Setup
void	init_data(t_data *data);
void init_angle(t_data *data);
int		are_args_valid(int argc, char **argv);

// rendering
void  draw_square(int i, int j,t_data *data, int col);
void	my_pixel_put(t_img *img, int x, int y, int color);
void render_map(t_data *data);
void draw_player(double i, double j, t_data *data);
// raycasting
void raycast(t_data *data);

// Handlers
int		handle_destroy(t_data *data);
int		handle_keypress(int keysym, t_data *data);

// Parsing
int		append_map_content(t_data *data, char *processed_line, char *line);
int		assign_texture(t_texture_type type, char *texture, t_data *data);
int		is_map_valid(t_data *data);
int		process_map(t_data *data);
int		is_surrounded_by_walls(t_data *data);
void	set_texture_ids(char *texture_ids[7]);

// Cleanup
void	free_textures(t_textures *textures);

#endif
