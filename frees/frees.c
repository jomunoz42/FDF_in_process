/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:09:13 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/04 20:51:36 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_char_map(char **map)
{
	char	**temp;

	temp = map;
	while (temp && *temp)
	{
		free(*temp);
		temp++;
	}
	free(map);
}

void	free_every_row_values(t_fdf *fdf)
{
	int	a;

	a = 0;
	while (a < fdf->map.height)
	{
		free(fdf->map.values[a]);
		a++;
	}
	free(fdf->map.values);
}

void	free_every_row_projected(t_fdf *fdf)
{
	int	a;

	a = 0;
	while (a < fdf->map.height)
	{
		free(fdf->map.projected[a]);
		a++;
	}
	free(fdf->map.projected);
}

void	free_up_to_failure_values(t_fdf *fdf, int allocated_rows)
{
	int	a;

	a = 0;
	while (a < allocated_rows)
	{
		free(fdf->map.values[a]);
		a++;
	}
	free(fdf->map.values);
}
