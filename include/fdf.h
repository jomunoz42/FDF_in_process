/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 22:19:53 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/04 23:21:51 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../minilibx-linux/mlx.h"
# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

# define MODE_ISOMETRIC 0
# define MODE_ORTHOGRAPHIC 1

# define WIN_WIDTH 1000
# define WIN_HEIGHT 800

# define KEY_ESC 65307
# define KEY_P 112
# define KEY_I 105
# define KEY_E 101
# define KEY_R 114
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_PLUS 65451
# define KEY_MINUS 65453
# define KEY_ESC 65307
# define KEY_ZERO 65436
# define KEY_ONE 65438

typedef struct s_point
{
	double	screen_x_rot;
	double	screen_y_rot;
}			t_point;

typedef struct s_box
{
	int		dx;
	int		dy;
	int		step_x;
	int		step_y;
	int		err;
	int		e2;
	int		z_fade;
	int		steps;
	int		i;
	float	t;
	int		x1;
	int		x2;
	int		y1;
	int		y2;
	int		z1;
	int		z2;
}			t_box;

typedef struct s_map
{
	t_point	**projected;
	int		**values;
	int		height;
	int		width;
	int		projection_mode;
	int		iso_mode;
	int		red;
	int		green;
	int		blue;
}			t_map;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_mlx;

typedef struct s_set
{
	int		margin;
	int		x_offset;
	int		y_offset;
	int		pixel_size;
	int		elevation;
	int		grid_span;
	int		range;
	int		change_elevation;
	double	alpha_x;
	double	alpha_y;
	double	alpha_z;
	double	x_rot;
	double	y_rot;
	double	z_rot;
}			t_set;

typedef struct s_fdf
{
	t_box	box;
	t_map	map;
	t_mlx	mlx;
	t_set	set;
}			t_fdf;

//=======================PARSING=========================

char		*get_next_line(int fd);
char		**get_map_with_style(int fd, int count);
void		get_int_map(t_fdf *fdf, char **map);

//=====================ASSIGNMENTS=======================

void		assign_map_configurations(t_fdf *fdf);
void		assign_mlx_functions(t_fdf *fdf);
void		assign_map_projected(t_fdf *fdf);
void		elevation_assignment(t_fdf *fdf);
void		assignments_allocations_and_keys(t_fdf *fdf, int fd);

//=======================DRAWING=========================

void		put_pixel(t_fdf *fdf, int x, int y, int colour);
void		bresenham_algorithm(t_fdf *fdf);
void		project_isometric(t_fdf *fdf);
void		project_orthographic(t_fdf *fdf);

//====================KEY_HANDLERS=======================

int			key_handler(int keycode, void *param);
int			key_handler6(int keycode, void *param);

//=======================UTILS===========================

int			find_biggest(t_fdf *fdf);
int			find_smallest(t_fdf *fdf);
int			return_smallest(int a, int b);
int			get_colour(int z, t_fdf *fdf);
void		window_to_black(void *addr, size_t size);
int			close_window(void *param);
void		rotate(double *x_rot, double *y_rot, double *z_rot, t_fdf *fdf);

//=======================FREES===========================

void		free_char_map(char **map);
void		free_every_row_values(t_fdf *fdf);
void		free_every_row_projected(t_fdf *fdf);
void		free_up_to_failure_values(t_fdf *fdf, int allocated_rows);
void		free_up_to_failure_projected(t_fdf *fdf, int allocated_rows);
void		free_everything(t_fdf *fdf);

#endif