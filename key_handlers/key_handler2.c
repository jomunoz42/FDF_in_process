/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:49:15 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/04 20:55:06 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	key_handler9(int keycode, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (keycode == KEY_I)
	{
		window_to_black(fdf->mlx.img_addr, fdf->mlx.line_len * WIN_HEIGHT);
		fdf->map.projection_mode = MODE_ISOMETRIC;
		fdf->set.change_elevation = 0;
		fdf->set.alpha_x = 0;
		fdf->set.alpha_y = 0;
		fdf->set.alpha_z = 0;
		fdf->set.x_offset = (WIN_WIDTH - ((fdf->map.width + fdf->map.height - 2)
					* (fdf->set.pixel_size / 2))) / 2;
		fdf->set.y_offset = (WIN_HEIGHT - ((fdf->map.width + fdf->map.height
						- 2) * (fdf->set.pixel_size / 2))) / 2;
		project_isometric(fdf);
	}
	return (0);
}

static int	key_handler8(int keycode, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (keycode == KEY_ZERO)
	{
		window_to_black(fdf->mlx.img_addr, fdf->mlx.line_len * WIN_HEIGHT);
		fdf->set.alpha_z -= 0.1;
		if (fdf->map.projection_mode == MODE_ISOMETRIC)
			project_isometric(fdf);
	}
	if (keycode == KEY_ONE)
	{
		window_to_black(fdf->mlx.img_addr, fdf->mlx.line_len * WIN_HEIGHT);
		fdf->set.alpha_z += 0.1;
		if (fdf->map.projection_mode == MODE_ISOMETRIC)
			project_isometric(fdf);
	}
	key_handler9(keycode, param);
	return (0);
}

static int	key_handler7(int keycode, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (keycode == KEY_LEFT)
	{
		window_to_black(fdf->mlx.img_addr, fdf->mlx.line_len * WIN_HEIGHT);
		fdf->set.alpha_x -= 0.1;
		if (fdf->map.projection_mode == MODE_ISOMETRIC)
			project_isometric(fdf);
	}
	if (keycode == KEY_RIGHT)
	{
		window_to_black(fdf->mlx.img_addr, fdf->mlx.line_len * WIN_HEIGHT);
		fdf->set.alpha_x += 0.1;
		if (fdf->map.projection_mode == MODE_ISOMETRIC)
			project_isometric(fdf);
	}
	key_handler8(keycode, param);
	return (0);
}

int	key_handler6(int keycode, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (keycode == KEY_UP)
	{
		window_to_black(fdf->mlx.img_addr, fdf->mlx.line_len * WIN_HEIGHT);
		fdf->set.alpha_y += 0.1;
		if (fdf->map.projection_mode == MODE_ISOMETRIC)
			project_isometric(fdf);
	}
	if (keycode == KEY_DOWN)
	{
		window_to_black(fdf->mlx.img_addr, fdf->mlx.line_len * WIN_HEIGHT);
		fdf->set.alpha_y -= 0.1;
		if (fdf->map.projection_mode == MODE_ISOMETRIC)
			project_isometric(fdf);
	}
	key_handler7(keycode, param);
	return (0);
}
