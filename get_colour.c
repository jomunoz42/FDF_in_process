/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colour.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 22:39:20 by jomunoz           #+#    #+#             */
/*   Updated: 2025/07/26 21:47:19 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_colour(int z, t_fdf *fdf)
{
	float	percent;
	int		min_z;
	int		max_z;
	int		red;
	int		green;
	int		blue;
	int		colour;

	min_z = find_smallest(fdf);
	max_z = find_biggest(fdf);
	percent = (float)(z - min_z) / (float)(max_z - min_z);
	(void)percent;
	red = 255 * percent;
	green = 50 * percent;
	blue = 100 * (1.0f - percent);
	colour = (red << 16) | (green << 8) | (blue << 0);
	return (colour);
}	
	


	/*
	if (percent <= 0.075)
		return (0xD8B5FF);
	if (percent <= 0.15)
		return (0xC8B4F6);
	if (percent <= 0.225)
		return (0xB9B4EE);
	if (percent <= 0.3)
		return (0xAAB3E5);
	if (percent <= 0.375)
		return (0x9AB3DD);
	if (percent <= 0.45)
		return (0x8BB2D4);
	if (percent <= 0.525)
		return (0x7BB1CB);
	if (percent <= 0.60)
		return (0x6BB1C3);
	else
		return (get_colour_helper(percent));
	*/
/*
int	get_colour_helper(float percent)
{
	if (percent <= 0.675)
		return (0x5CB0BA);
	if (percent <= 0.76)
		return (0x4DB0B2);
	if (percent <= 0.84)
		return (0x3DAFA9);
	if (percent <= 0.91)
		return (0x2EAFA1);
	if (percent <= 1)
		return (0xEAE98);
	else
		return (1);
}
*/
