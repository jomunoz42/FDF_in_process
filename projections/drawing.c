/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 22:18:26 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/05 19:35:17 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(t_fdf *fdf, int x, int y, int colour)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
		return ;
	dst = fdf->mlx.img_addr + (y * fdf->mlx.line_len + x * (fdf->mlx.bpp / 8));
	*(unsigned int *)dst = colour;
}

static void	bresenham_algorithm_part2(int *x1, int *y1, t_fdf *fdf)
{
	if (fdf->box.e2 >= -fdf->box.dy)
	{
		fdf->box.err -= fdf->box.dy;
		*x1 += fdf->box.step_x;
	}
	if (fdf->box.e2 <= fdf->box.dx)
	{
		fdf->box.err += fdf->box.dx;
		*y1 += fdf->box.step_y;
	}
}

static void	colour_interpolation(t_fdf *fdf)
{
	if (fdf->box.steps == 0)
		fdf->box.t = 0.0f;
	else
		fdf->box.t = (float)fdf->box.i / fdf->box.steps;
	fdf->box.z_fade = (1 - fdf->box.t) * fdf->box.z1 + fdf->box.t * fdf->box.z2;
}

void	bresenham_algorithm(t_fdf *fdf)
{
	t_box	*b;

	b = &fdf->box;
	b->dx = abs(b->x2 - b->x1);
	b->dy = abs(b->y2 - b->y1);
	b->step_x = (b->x1 < b->x2) - (b->x1 >= b->x2);
	b->step_y = (b->y1 < b->y2) - (b->y1 >= b->y2);
	if (b->dx > b->dy)
		b->steps = b->dx;
	else
		b->steps = b->dy;
	b->err = b->dx - b->dy;
	b->i = 0;
	while (1)
	{
		colour_interpolation(fdf);
		put_pixel(fdf, b->x1, b->y1, get_colour(b->z_fade, fdf));
		if (b->x1 == b->x2 && b->y1 == b->y2)
			break ;
		b->e2 = 2 * b->err;
		bresenham_algorithm_part2(&b->x1, &b->y1, fdf);
		b->i++;
	}
}
