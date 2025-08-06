/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:49:28 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/04 20:51:42 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_up_to_failure_projected(t_fdf *fdf, int allocated_rows)
{
	int	a;

	a = 0;
	while (a < allocated_rows)
	{
		free(fdf->map.projected[a]);
		a++;
	}
	free(fdf->map.projected);
	free_every_row_values(fdf);
}

void	free_everything(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx.mlx_ptr, fdf->mlx.img_ptr);
	free_every_row_values(fdf);
	free_every_row_projected(fdf);
}
