/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:03:23 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/04 21:39:18 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	**get_map_with_style(int fd, int count)
{
	char	*line;
	char	**map;

	map = NULL;
	line = get_next_line(fd);
	if (line != NULL)
		map = get_map_with_style(fd, count + 1);
	else if (count)
	{
		map = malloc(sizeof(char *) * (count + 1));
		{
			if (!map)
			{
				perror("Allocation failed in get_map_with_style");
				exit(1);
			}
		}
	}
	if (map)
		map[count] = line;
	return (map);
}

static int	ft_atol(char **nb)
{
	int		a;
	int		sign;
	long	num;

	a = 0;
	num = 0;
	while (nb[0][a] == ' ')
		a++;
	sign = (nb[0][a] != '-') - (nb[0][a] == '-');
	a += (nb[0][a] == '-') || (nb[0][a] == '+');
	while (nb[0][a] >= '0' && nb[0][a] <= '9')
		num = num * 10 + (nb[0][a++] - '0');
	while (nb[0][a] == ' ')
		a++;
	nb[0] += a;
	return (num * sign);
}

static size_t	ft_count_words(char const *s, char d)
{
	int	a;
	int	count;

	a = 0;
	count = 0;
	while (s[a])
	{
		if ((s[a] != d && (a == 0 || s[a - 1] == d)))
			count++;
		a++;
	}
	return (count);
}

static void	alloc_map(t_fdf *fdf, char **map)
{
	int	a;

	a = 0;
	while (map[a])
		a++;
	fdf->map.height = a;
	fdf->map.width = ft_count_words(map[fdf->map.height - 1], ' ');
	fdf->map.values = malloc(sizeof(int *) * fdf->map.height);
}

void	get_int_map(t_fdf *fdf, char **map)
{
	int		a;
	int		b;
	char	*line;

	a = 0;
	alloc_map(fdf, map);
	while (a < fdf->map.height)
	{
		fdf->map.values[a] = malloc(sizeof(int) * fdf->map.width);
		if (!fdf->map.values[a])
		{
			free_up_to_failure_values(fdf, a);
			exit(1);
		}
		line = map[a];
		b = 0;
		while (b < fdf->map.width)
		{
			fdf->map.values[a][b] = ft_atol(&line);
			b++;
		}
		a++;
	}
	free_char_map(map);
}
