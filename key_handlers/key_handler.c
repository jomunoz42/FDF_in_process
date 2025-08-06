/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 21:03:33 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/04 20:54:05 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	key_handler5(int keycode, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (keycode == KEY_PLUS)
	{
		window_to_black(fdf->mlx.img_addr, fdf->mlx.line_len * WIN_HEIGHT);
		fdf->set.pixel_size += 3;
		if (fdf->map.projection_mode == MODE_ISOMETRIC)
			project_isometric(fdf);
		else
			project_orthographic(fdf);
	}
	if (keycode == KEY_MINUS)
	{
		window_to_black(fdf->mlx.img_addr, fdf->mlx.line_len * WIN_HEIGHT);
		if (fdf->set.pixel_size > 4)
			fdf->set.pixel_size -= 3;
		if (fdf->map.projection_mode == MODE_ISOMETRIC)
			project_isometric(fdf);
		else
			project_orthographic(fdf);
	}
	return (0);
}

static int	key_handler4(int keycode, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (keycode == KEY_A)
	{
		window_to_black(fdf->mlx.img_addr, fdf->mlx.line_len * WIN_HEIGHT);
		fdf->set.x_offset -= 25;
		if (fdf->map.projection_mode == MODE_ISOMETRIC)
			project_isometric(fdf);
		else
			project_orthographic(fdf);
	}
	if (keycode == KEY_D)
	{
		window_to_black(fdf->mlx.img_addr, fdf->mlx.line_len * WIN_HEIGHT);
		fdf->set.x_offset += 25;
		if (fdf->map.projection_mode == MODE_ISOMETRIC)
			project_isometric(fdf);
		else
			project_orthographic(fdf);
	}
	key_handler5(keycode, param);
	return (0);
}

static int	key_handler3(int keycode, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (keycode == KEY_W)
	{
		window_to_black(fdf->mlx.img_addr, fdf->mlx.line_len * WIN_HEIGHT);
		fdf->set.y_offset -= 25;
		if (fdf->map.projection_mode == MODE_ISOMETRIC)
			project_isometric(fdf);
		else
			project_orthographic(fdf);
	}
	if (keycode == KEY_S)
	{
		window_to_black(fdf->mlx.img_addr, fdf->mlx.line_len * WIN_HEIGHT);
		fdf->set.y_offset += 25;
		if (fdf->map.projection_mode == MODE_ISOMETRIC)
			project_isometric(fdf);
		else
			project_orthographic(fdf);
	}
	key_handler4(keycode, param);
	return (0);
}

static int	key_handler2(int keycode, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (keycode == KEY_E)
	{
		window_to_black(fdf->mlx.img_addr, fdf->mlx.line_len * WIN_HEIGHT);
		fdf->set.change_elevation += 1;
		if (fdf->map.projection_mode == MODE_ISOMETRIC)
			project_isometric(fdf);
	}
	if (keycode == KEY_R)
	{
		window_to_black(fdf->mlx.img_addr, fdf->mlx.line_len * WIN_HEIGHT);
		fdf->set.change_elevation -= 1;
		if (fdf->map.projection_mode == MODE_ISOMETRIC)
			project_isometric(fdf);
	}
	key_handler3(keycode, param);
	return (0);
}

int	key_handler(int keycode, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (keycode == KEY_ESC)
		close_window((void *)param);
	if (keycode == KEY_P)
	{
		window_to_black(fdf->mlx.img_addr, fdf->mlx.line_len * WIN_HEIGHT);
		fdf->map.projection_mode = MODE_ORTHOGRAPHIC;
		project_orthographic(fdf);
	}
	key_handler2(keycode, param);
	key_handler6(keycode, param);
	return (0);
}
