/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryagoub <ryagoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:51:19 by maabdull          #+#    #+#             */
/*   Updated: 2024/09/28 13:48:42 by ryagoub          ###   ########.fr       */
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

# define SQUARE 32
# define TEXTURE 64
# define SPEED 0.005
# define SENSITIVITY 0.005
# define PI 3.14159265359
# define WIDTH 1024
# define HEIGHT 512
# define R_SPEED 1

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
	int		floor[3];
	int		ceiling[3];
}	t_textures;

typedef struct s_coords
{
	int	x;
	int	y;
}	t_coords;

typedef struct s_player
{
	char	direction;
	int		angle;
	int		angle_multiplier;
	float		x;
	float		y;
	t_coords	velocity;
}	t_player;

typedef struct s_img {
	void	*img;
	int		*img_pixels_ptr;
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
	t_img       north;
	int			nh;
	int			nw;
	t_img       south;
	int			sh;
	int			sw;
	t_img       east;
	int			eh;
	int			ew;
	t_img       west;
	int			wh;
	int			ww;
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
// Linux keycodes
#  define KEY_ESC 65307
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_Q 113
#  define KEY_ARROW_UP 65362
#  define KEY_ARROW_LEFT 65361
#  define KEY_ARROW_DOWN 65364
#  define KEY_ARROW_RIGHT 65363
# else
// macOS key code macros
#  define KEY_ESC 53
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_Q 12
#  define KEY_ARROW_UP 126
#  define KEY_ARROW_LEFT 123
#  define KEY_ARROW_DOWN 125
#  define KEY_ARROW_RIGHT 124
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
void draw_background(t_data *data);
// raycasting
void raycast(t_data *data);

// Handlers
int		handle_destroy(t_data *data);
int		handle_keypress(int keysym, t_data *data);
int		handle_keyrelease(int keysym, t_data *data);

// Parsing
int		append_map_content(t_data *data, char *processed_line, char *line);
int		assign_texture(t_texture_type type, char *texture, t_data *data);
int		is_map_valid(t_data *data);
int		process_map(t_data *data);
int		is_surrounded_by_walls(t_data *data);
void	set_texture_ids(char *texture_ids[7]);

// textures
int	save_images(t_data *data);
void	draw_image(t_data *data, int wall_length, int rays_count, int flag, \
	float ray_angle);
	int	rgb_to_hex(int rgb[3]);

// Cleanup
void	free_textures(t_textures *textures);

#endif
