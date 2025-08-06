/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assigments.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 20:21:02 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/04 20:46:05 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	assign_mlx_functions(t_fdf *fdf)
{
	fdf->mlx.mlx_ptr = mlx_init();
	fdf->mlx.win_ptr = mlx_new_window(fdf->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			"FDF");
	fdf->mlx.img_ptr = mlx_new_image(fdf->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	fdf->mlx.img_addr = mlx_get_data_addr(fdf->mlx.img_ptr, &fdf->mlx.bpp,
			&fdf->mlx.line_len, &fdf->mlx.endian);
}

void	assign_map_configurations(t_fdf *fdf)
{
	int	avail_width;
	int	avail_height;
	int	pixel_width;
	int	pixel_height;
	int	diag_len;

	fdf->set.margin = return_smallest(WIN_WIDTH, WIN_HEIGHT) / 4;
	diag_len = fdf->map.width + fdf->map.height - 2;
	avail_width = WIN_WIDTH - 2 * fdf->set.margin;
	avail_height = WIN_HEIGHT - 2 * fdf->set.margin;
	pixel_width = avail_width / diag_len;
	pixel_height = (2 * avail_height) / diag_len;
	fdf->set.pixel_size = return_smallest(pixel_width, pixel_height);
	fdf->set.x_offset = (WIN_WIDTH - ((fdf->map.width + fdf->map.height - 2)
				* (fdf->set.pixel_size / 2))) / 2;
	fdf->set.y_offset = (WIN_HEIGHT - ((fdf->map.width + fdf->map.height - 2)
				* (fdf->set.pixel_size / 2))) / 2;
}

void	assign_map_projected(t_fdf *fdf)
{
	int	a;

	a = 0;
	fdf->map.projected = malloc(sizeof(t_point *) * fdf->map.height);
	if (!fdf->map.projected)
	{
		free_every_row_values(fdf);
		exit(1);
	}
	while (a < fdf->map.height)
	{
		fdf->map.projected[a] = malloc(sizeof(t_point) * fdf->map.width);
		if (!fdf->map.projected[a])
		{
			free_up_to_failure_projected(fdf, a);
			free_every_row_values(fdf);
			exit(1);
		}
		a++;
	}
}

void	elevation_assignment(t_fdf *fdf)
{
	fdf->set.range = find_biggest(fdf) - find_smallest(fdf);
	if (fdf->set.range == 0)
		fdf->set.range = 1;
	fdf->set.grid_span = return_smallest(fdf->map.width, fdf->map.height);
	fdf->set.elevation = ((fdf->set.pixel_size * (fdf->set.grid_span / 4))
			/ fdf->set.range) + fdf->set.change_elevation;
}

void	assignments_allocations_and_keys(t_fdf *fdf, int fd)
{
	get_int_map(fdf, get_map_with_style(fd, 0));
	assign_mlx_functions(fdf);
	assign_map_configurations(fdf);
	assign_map_projected(fdf);
	mlx_hook(fdf->mlx.win_ptr, 17, 0, close_window, fdf);
	mlx_key_hook(fdf->mlx.win_ptr, key_handler, fdf);
}
