/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 22:19:53 by jomunoz           #+#    #+#             */
/*   Updated: 2025/07/27 20:15:10 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "minilibx-linux/mlx.h"
# include <math.h>
# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

#define MODE_ISOMETRIC    0
#define MODE_ORTHOGRAPHIC 1

# define WIN_WIDTH 1000
# define WIN_HEIGHT 800

#define KEY_ESC   65307
#define KEY_P     112
#define KEY_I     105
#define KEY_E     101
#define KEY_R     114
#define KEY_W     119
#define KEY_A	  97
#define KEY_S     115
#define KEY_D	  100
#define KEY_UP    65362
#define KEY_DOWN  65364
#define KEY_LEFT  65361
#define KEY_RIGHT 65363
#define KEY_PLUS  65451
#define KEY_MINUS 65453

typedef struct s_point 
{
    int 	screen_x;
    int 	screen_y;
} 			t_point;

typedef struct s_rotated
{
	double	screen_x_rot;
	double	screen_y_rot;
}			t_rotated;

typedef struct s_map
{
	t_rotated 	**projected_rot;
	t_point		**projected;
	int			**values;
	int			height;
	int			width;
	int			mode;
}				t_map;

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
    int     margin;
    int     x_offset;
    int     y_offset;
    int     pixel_size;
	int		change_elevation;
	double	rotation_x;
	double	rotation_y;
	double	rotation_z;
}           t_set;

typedef struct s_fdf
{
	t_map 	map;
	t_mlx	mlx;
	t_set 	set;
} 			t_fdf;


int		close_window(void *param);

//=====================ASSIGNMENTS=======================

void 		assign_map_configurations(t_fdf *fdf);
void 		assign_mlx_functions(t_fdf *fdf);
void 		assign_map_projected(t_fdf *fdf);
void    	assign_map_projected_rot(t_fdf *fdf);



//=======================DRAWING=========================

void    	project_isometric(t_fdf *fdf);
void		project_orthographic(t_fdf *fdf);
void    	project_isometric_rot(t_fdf *fdf);


//=======================PARSING=========================

char		**get_map_with_style(int fd, int count);
void    	get_int_map(t_fdf *fdf, char **char_map);

//=======================UTILS===========================

char		*get_next_line(int fd);
int 		find_biggest(t_fdf *fdf);
int			find_smallest(t_fdf *fdf);
int         return_smallest(int a, int  b);
void    	free_every_row(t_fdf *fdf, int allocated_rows);

//=======================BONUS===========================

int 		get_colour(int z, t_fdf *fdf);

#endif