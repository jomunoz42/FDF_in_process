/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assigments.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 20:21:02 by jomunoz           #+#    #+#             */
/*   Updated: 2025/07/27 20:02:23 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void        assign_mlx_functions(t_fdf *fdf)
{
    fdf->mlx.mlx_ptr = mlx_init();
    fdf->mlx.win_ptr = mlx_new_window(fdf->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FDF");
    fdf->mlx.img_ptr = mlx_new_image(fdf->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
    fdf->mlx.img_addr = mlx_get_data_addr(fdf->mlx.img_ptr, &fdf->mlx.bpp, &fdf->mlx.line_len, &fdf->mlx.endian);
}

void        assign_map_configurations(t_fdf *fdf)
{
    int avail_width;
    int avail_height;
    int pixel_width;
    int pixel_height;
    int diag_len;

    fdf->set.margin = return_smallest(WIN_WIDTH, WIN_HEIGHT) / 4;
    
    diag_len = fdf->map.width + fdf->map.height - 2;
    avail_width  = WIN_WIDTH  - 2 * fdf->set.margin;
    avail_height = WIN_HEIGHT - 2 * fdf->set.margin;
    
    pixel_width  = avail_width  / diag_len;
    pixel_height = (2 * avail_height) / diag_len;
    
    fdf->set.pixel_size = return_smallest(pixel_width, pixel_height);

    fdf->set.x_offset = (WIN_WIDTH - (diag_len * (fdf->set.pixel_size / 2))) / 2;
    fdf->set.y_offset = (WIN_HEIGHT - (diag_len * (fdf->set.pixel_size / 2))) / 2;

    fdf->set.change_elevation = 0;
    fdf->map.mode = MODE_ISOMETRIC;
    fdf->set.rotation_x = 0;
    fdf->set.rotation_y = 0;
    fdf->set.rotation_z = 0;
}

void    assign_map_projected(t_fdf *fdf)
{
    int a;

    a = 0;
    fdf->map.projected = malloc(sizeof(t_point *) * fdf->map.height);
    if (!fdf->map.projected)
    {
        free(fdf->map.projected);
    }
    while (a < fdf->map.height)
    {
        fdf->map.projected[a] = malloc(sizeof(t_point) * fdf->map.width);
        if (!fdf->map.projected[a])
        {
            free_every_row(fdf, a);
        }
        a++;
    }
}

void    assign_map_projected_rot(t_fdf *fdf)
{
    int a;

    a = 0;
    fdf->map.projected_rot = malloc(sizeof(t_point *) * fdf->map.height);
    if (!fdf->map.projected_rot)
    {
        free(fdf->map.projected_rot);// see why its wrong
    }
    while (a < fdf->map.height)
    {
        fdf->map.projected_rot[a] = malloc(sizeof(t_point) * fdf->map.width);
        if (!fdf->map.projected_rot[a])
        {
            free_every_row(fdf, a);///// see correct free
        }
        a++;
    }
}




// t_set   *assign_map_configurations(t_map *map)          old correct one for 2d grid
// {
//     t_set   *set;
    
//     set = malloc(sizeof(t_set));
//     if (!set)
//         return (NULL);
//     set->margin = return_smallest(WIN_WIDTH, WIN_HEIGHT) / 3;
//     set->pixel_size = return_smallest((WIN_WIDTH - 2 * set->margin) / map->width, (WIN_HEIGHT - 2 * set->margin) / map->height);
//     set->x_offset = (WIN_WIDTH - (map->width * set->pixel_size)) / 2;
//     set->y_offset = (WIN_HEIGHT - (map->height * set->pixel_size)) / 2;
//     return(set);
// }
