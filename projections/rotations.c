/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 22:18:26 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/04 22:58:53 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rot_x(double *y, double *z, double alpha_x)
{
	double	temp_y;

	temp_y = *y;
	*y = temp_y * cos(alpha_x) - (*z) * sin(alpha_x);
	*z = temp_y * sin(alpha_x) + (*z) * cos(alpha_x);
}

static void	rot_y(double *x, double *z, double alpha_y)
{
	double	temp_x;

	temp_x = *x;
	*x = temp_x * cos(alpha_y) + (*z) * sin(alpha_y);
	*z = -temp_x * sin(alpha_y) + (*z) * cos(alpha_y);
}

static void	rot_z(double *x, double *y, double alpha_z)
{
	double	temp_x;

	temp_x = *x;
	*x = temp_x * cos(alpha_z) - (*y) * sin(alpha_z);
	*y = temp_x * sin(alpha_z) + (*y) * cos(alpha_z);
}

void	rotate(double *x_rot, double *y_rot, double *z_rot, t_fdf *fdf)
{
	rot_x(y_rot, z_rot, fdf->set.alpha_x);
	rot_y(x_rot, z_rot, fdf->set.alpha_y);
	rot_z(x_rot, y_rot, fdf->set.alpha_z);
}
