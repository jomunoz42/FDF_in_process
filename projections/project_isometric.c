/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_isometric.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:37:15 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/04 22:39:19 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	drawing_isometric_grid3(int x, int y, t_fdf *fdf)
{
	t_box	*b;

	b = &fdf->box;
	if (y + 1 < fdf->map.height)
	{
		b->x1 = fdf->set.x_offset + fdf->map.projected[y][x].screen_x_rot;
		b->y1 = fdf->set.y_offset + fdf->map.projected[y][x].screen_y_rot;
		b->x2 = fdf->set.x_offset + fdf->map.projected[y + 1][x].screen_x_rot;
		b->y2 = fdf->set.y_offset + fdf->map.projected[y + 1][x].screen_y_rot;
		b->z1 = fdf->map.values[y][x];
		b->z2 = fdf->map.values[y + 1][x];
		bresenham_algorithm(fdf);
	}
}

static void	drawing_isometric_grid2(int x, int y, t_fdf *fdf)
{
	t_box	*b;

	b = &fdf->box;
	if (x + 1 < fdf->map.width)
	{
		b->x1 = fdf->set.x_offset + fdf->map.projected[y][x].screen_x_rot;
		b->y1 = fdf->set.y_offset + fdf->map.projected[y][x].screen_y_rot;
		b->x2 = fdf->set.x_offset + fdf->map.projected[y][x + 1].screen_x_rot;
		b->y2 = fdf->set.y_offset + fdf->map.projected[y][x + 1].screen_y_rot;
		b->z1 = fdf->map.values[y][x];
		b->z2 = fdf->map.values[y][x + 1];
		bresenham_algorithm(fdf);
	}
}

static void	drawing_isometric_grid(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			drawing_isometric_grid2(x, y, fdf);
			drawing_isometric_grid3(x, y, fdf);
			x++;
		}
		y++;
	}
}

static void	isometric_conversion(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	elevation_assignment(fdf);
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			fdf->set.x_rot = (double)x;
			fdf->set.y_rot = (double)y;
			fdf->set.z_rot = (double)fdf->map.values[y][x];
			rotate(&fdf->set.x_rot, &fdf->set.y_rot, &fdf->set.z_rot, fdf);
			fdf->map.projected[y][x].screen_x_rot = (fdf->set.x_rot
					- fdf->set.y_rot) * fdf->set.pixel_size;
			fdf->map.projected[y][x].screen_y_rot = (fdf->set.x_rot
					+ fdf->set.y_rot) * (fdf->set.pixel_size / 2)
				- (fdf->map.values[y][x] * fdf->set.elevation);
			x++;
		}
		y++;
	}
}

void	project_isometric(t_fdf *fdf)
{
	int		x;
	int		y;
	double	cx;
	double	cy;

	x = 0;
	y = 0;
	isometric_conversion(fdf);
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			cx = fdf->set.x_offset + fdf->map.projected[y][x].screen_x_rot;
			cy = fdf->set.y_offset + fdf->map.projected[y][x].screen_y_rot;
			put_pixel(fdf, cx, cy, get_colour(fdf->map.values[y][x], fdf));
			x++;
		}
		y++;
	}
	drawing_isometric_grid(fdf);
	mlx_put_image_to_window(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr,
		fdf->mlx.img_ptr, 0, 0);
}
