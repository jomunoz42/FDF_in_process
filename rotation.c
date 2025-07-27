/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:37:15 by jomunoz           #+#    #+#             */
/*   Updated: 2025/07/27 21:05:36 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void put_pixel(char *addr, int x, int y, int colour, int line_len, int bpp)
{
    char *dst;

    if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
    {
        write (2, "Error: drawing out of bounds\n", 30);
        return;
    }
    dst = addr + (y * line_len + x * (bpp / 8));
    *(unsigned int *)dst = colour;
}

static void    isometric_bresenham(int x1, int y1, int x2, int y2, int z1, int z2, t_fdf *fdf)
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

static void    drawing_isometric_grid_rot(t_fdf *fdf)
{
    int     x;
    int     y;
    double     cx;
    double     cy;
    double     cx2;
    double     cy2;

    y = 0;
    while (y < fdf->map.height)
    {
        x = 0;
        while (x < fdf->map.width)
        {
            cx = fdf->set.x_offset + fdf->map.projected_rot[y][x].screen_x_rot;
            cy = fdf->set.y_offset + fdf->map.projected_rot[y][x].screen_y_rot;

            if (x + 1 < fdf->map.width)
            {
                cx2 = fdf->set.x_offset + fdf->map.projected_rot[y][x + 1].screen_x_rot;
                cy2 = fdf->set.y_offset + fdf->map.projected_rot[y][x + 1].screen_y_rot;
                isometric_bresenham(cx, cy, cx2, cy2, fdf->map.values[y][x], fdf->map.values[y][x + 1], fdf);
            }
            if (y + 1 < fdf->map.height)
            {
                cx2 = fdf->set.x_offset + fdf->map.projected_rot[y + 1][x].screen_x_rot;
                cy2 = fdf->set.y_offset + fdf->map.projected_rot[y + 1][x].screen_y_rot;
                isometric_bresenham(cx, cy, cx2, cy2, fdf->map.values[y][x], fdf->map.values[y + 1][x], fdf);
            }
            x++;
        }
        y++;
    }
}

static  void    rotate_x (double x, double y, double z, double alpha, double *x_rot, double *y_rot, double *z_rot)
{
    printf("Rotation angle X (radians): %.3f\n", alpha);
    *x_rot = x;
    *y_rot = y * cos(alpha) - z * sin(alpha);
    *z_rot = y * sin(alpha) + z * cos(alpha);
}

static void     isometric_conversion_rot(t_fdf *fdf)
{
    int x;
    int y;
    int elevation;
    int grid_span;
    int range;
    double x_rot;
    double y_rot;
    double z_rot;
    double alpha;

    alpha = fdf->set.rotation_x;
    y = 0;
    range = find_biggest(fdf) - find_smallest(fdf);
    if (range == 0)
        range = 1;
    grid_span = return_smallest(fdf->map.width, fdf->map.height);
    elevation = ((fdf->set.pixel_size * (grid_span / 4)) / range) + fdf->set.change_elevation;
    while(y < fdf->map.height)
    {
        x = 0;
        while (x < fdf->map.width)
        {
            rotate_x(x, y, (double)fdf->map.values[y][x], alpha, &x_rot, &y_rot, &z_rot);
            // printf("Point (%d,%d): orig_z=%d, rotated=(%.3f, %.3f, %.3f), projected_x=%.3f, projected_y=%.3f\n",
            //        x, y,
            //        fdf->map.values[y][x],
            //        x_rot, y_rot, z_rot,
            //        fdf->map.projected_rot[y][x].screen_x_rot, fdf->map.projected_rot[y][x].screen_x_rot );
            fdf->map.projected_rot[y][x].screen_x_rot = (x_rot - y_rot) * fdf->set.pixel_size;
            fdf->map.projected_rot[y][x].screen_y_rot = (x_rot + y_rot) * (fdf->set.pixel_size / 2) - (z_rot * elevation);
            x++;
        }
        y++;
    }
}

void    project_isometric_rot(t_fdf *fdf)
{
    int     x;
    int     y;
    double   cx;
    double   cy;

    x = 0;
    y = 0;
    isometric_conversion_rot(fdf);
    while(y < fdf->map.height)
    {
        x = 0;
        while(x < fdf->map.width)
        {

            cx = fdf->set.x_offset + fdf->map.projected_rot[y][x].screen_x_rot;
            cy = fdf->set.y_offset + fdf->map.projected_rot[y][x].screen_y_rot;
            // printf("Drawing pixel at (%d, %d) with color %x\n", cx, cy, get_colour(fdf->map.values[y][x], fdf));
            put_pixel(fdf->mlx.img_addr, cx, cy, get_colour(fdf->map.values[y][x], fdf), fdf->mlx.line_len, fdf->mlx.bpp);
            x++;
        }
        y++;
    }
    drawing_isometric_grid_rot(fdf);
    mlx_put_image_to_window(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr, fdf->mlx.img_ptr, 0, 0);
}
