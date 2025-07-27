/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_orthographic.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 22:50:18 by jomunoz           #+#    #+#             */
/*   Updated: 2025/07/27 15:16:58 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	put_pixel(char *addr, int x, int y, int colour, int line_len,
		int bpp)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
	{
		write(2, "Error: drawing out of bounds\n", 30);
		return ;
	}
	dst = addr + (y * line_len + x * (bpp / 8));
	*(unsigned int *)dst = colour;
}

static void    orthographic_bresenham(int x1, int y1, int x2, int y2, int z1, int z2, t_fdf *fdf)
{
    int dx;
    int dy;
    int step_x;
    int step_y;
    int err;
    int e2;
    int colour;
    int z_fade;
    int steps;
    int i;
    float t;
    
    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    step_x = (x1 < x2) - (x1 >= x2);
    step_y = (y1 < y2) - (y1 >= y2);
    if (dx > dy)
        steps = dx;
    else
        steps = dy;
    i = 0;
    err = dx - dy;
    while (1)
    {
        if (steps == 0)
            t = 0.0f;
        else
            t = (float)i / steps;
        z_fade = (1 - t) * z1 + t * z2;
        colour = get_colour(z_fade, fdf);
        put_pixel(fdf->mlx.img_addr, x1, y1, colour, fdf->mlx.line_len, fdf->mlx.bpp);
        if (x1 == x2 && y1 == y2)
            break;
        e2 = 2 * err;
        if (e2 >= -dy)
        {
            err -= dy;
            x1 += step_x;
        }
        if (e2 <= dx)
        {
            err += dx;
            y1 += step_y;
        }
        i++;
    }
}

static void	draw_orthographic_grid(t_fdf *fdf)
{
	int	x;
	int	y;
	int	cx;
	int	cy;
	int	cx2;
	int	cy2;

	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			cx = fdf->set.x_offset + x * fdf->set.pixel_size - 50;
			cy = fdf->set.y_offset + y * fdf->set.pixel_size;
			if (x + 1 < fdf->map.width)
			{
				cx2 = fdf->set.x_offset + (x + 1) * fdf->set.pixel_size - 50;
				cy2 = fdf->set.y_offset + y * fdf->set.pixel_size;
				orthographic_bresenham(cx, cy, cx2, cy2, fdf->map.values[y][x], fdf->map.values[y][x + 1], fdf);
			}
			if (y + 1 < fdf->map.height)
			{
				cx2 = fdf->set.x_offset + x * fdf->set.pixel_size - 50;
				cy2 = fdf->set.y_offset + (y + 1) * fdf->set.pixel_size;
				orthographic_bresenham(cx, cy, cx2, cy2, fdf->map.values[y][x], fdf->map.values[y + 1][x], fdf);
			}
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
			put_pixel(fdf->mlx.img_addr, cx, cy, 0xFFFFFF, fdf->mlx.line_len, fdf->mlx.bpp);
			x++;
		}
		y++;
	}
	draw_orthographic_grid(fdf);
	mlx_put_image_to_window(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr, fdf->mlx.img_ptr, 0, 0);
}
