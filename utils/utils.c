/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 17:22:43 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/05 19:08:11 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_colour(int z, t_fdf *fdf)
{
	float	percent;
	int		min_z;
	int		max_z;
	int		colour;

	min_z = find_smallest(fdf);
	max_z = find_biggest(fdf);
	if (max_z == min_z)
		return (0xFF8C00);
	percent = (float)(z - min_z) / (float)(max_z - min_z);
	(void)percent;
	fdf->map.red = 255 * percent;
	fdf->map.green = 50 * percent;
	fdf->map.blue = 150 * (1.0f - percent);
	colour = (fdf->map.red << 16) | (fdf->map.green << 8)
		| (fdf->map.blue << 0);
	return (colour);
}

int	close_window(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	free_everything(fdf);
	exit(0);
	return (0);
}

void	window_to_black(void *addr, size_t size)
{
	size_t			a;
	unsigned char	*buffer1;

	buffer1 = addr;
	a = 0;
	while (a < size)
	{
		buffer1[a] = 0;
		a++;
	}
}
