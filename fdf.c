/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 22:18:26 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/05 19:45:34 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char *argv[])
{
	static t_fdf	fdf;
	char			buffer;
	int				fd;

	if (argc != 2)
	{
		write(2, "Error, invalid number of arguments\n", 36);
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error, non existent file or unreadable");
		exit(1);
	}
	if (read(fd, &buffer, 1) <= 0)
	{
		write(2, "Error, empty file or unreadable\n", 33);
		exit(1);
	}
	assignments_allocations_and_keys(&fdf, fd);
	project_isometric(&fdf);
	mlx_loop(fdf.mlx.mlx_ptr);
	close(fd);
	return (free_everything(&fdf), 0);
}
