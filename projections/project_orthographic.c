/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_orthographic.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 22:50:18 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/04 20:52:39 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_orthographic_grid3(int x, int y, t_fdf *fdf)
{
	t_box	*b;

	b = &fdf->box;
	if (x + 1 < fdf->map.width)
	{
		b->x1 = fdf->set.x_offset + x * fdf->set.pixel_size - 50;
		b->y1 = fdf->set.y_offset + y * fdf->set.pixel_size;
		b->x2 = fdf->set.x_offset + (x + 1) * fdf->set.pixel_size - 50;
		b->y2 = fdf->set.y_offset + y * fdf->set.pixel_size;
		b->z1 = fdf->map.values[y][x];
		b->z2 = fdf->map.values[y][x + 1];
		bresenham_algorithm(fdf);
	}
}

static void	draw_orthographic_grid2(int x, int y, t_fdf *fdf)
{
	t_box	*b;

	b = &fdf->box;
	if (y + 1 < fdf->map.height)
	{
		b->x1 = fdf->set.x_offset + x * fdf->set.pixel_size - 50;
		b->y1 = fdf->set.y_offset + y * fdf->set.pixel_size;
		b->x2 = fdf->set.x_offset + x * fdf->set.pixel_size - 50;
		b->y2 = fdf->set.y_offset + (y + 1) * fdf->set.pixel_size;
		b->z1 = fdf->map.values[y][x];
		b->z2 = fdf->map.values[y + 1][x];
		bresenham_algorithm(fdf);
	}
}

static void	draw_orthographic_grid(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			draw_orthographic_grid2(x, y, fdf);
			draw_orthographic_grid3(x, y, fdf);
			x++;
		}
		y++;
	}
}

void	project_orthographic(t_fdf *fdf)
{
	int	x;
	int	y;
	int	cx;
	int	cy;

	x = 0;
	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			cx = fdf->set.x_offset + x * fdf->set.pixel_size - 50;
			cy = fdf->set.y_offset + y * fdf->set.pixel_size;
			put_pixel(fdf, cx, cy, 0xFFFFFF);
			x++;
		}
		y++;
	}
	draw_orthographic_grid(fdf);
	mlx_put_image_to_window(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr,
		fdf->mlx.img_ptr, 0, 0);
}
