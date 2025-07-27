/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:03:23 by jomunoz           #+#    #+#             */
/*   Updated: 2025/07/26 21:08:06 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char    **get_map_with_style(int fd, int count)
{
    char *line;
    char **map;

    map = NULL;
    line = get_next_line(fd);
    if (line != NULL)
        map = get_map_with_style(fd, count + 1);
    else if (count)
        map = malloc(sizeof(char *) * (count + 1));
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

void     alloc_map(t_fdf *fdf, char **char_map)
{
    int     a;

    a = 0;
    while (char_map[a])
        a++;
    fdf->map.height = a;
    fdf->map.width = ft_count_words(char_map[0], ' ');
    fdf->map.values = malloc(sizeof(int *) * fdf->map.height);
    if (!fdf->map.values)
    {
        free(fdf->map.values);
        exit(1);
    }
}

void    get_int_map(t_fdf *fdf, char **char_map)
{
    int a;
    int b;
    char *line;

    a = 0;
    alloc_map(fdf, char_map);
    while (a < fdf->map.height)
    {
        fdf->map.values[a] = malloc(sizeof(int) * fdf->map.width);
        if (!fdf->map.values[a])
        {
            free_every_row(fdf, a);
            exit(1);
        }
        line = char_map[a];
        b = 0;
        while (b < fdf->map.width)
        {
            fdf->map.values[a][b] = ft_atol(&line);
            b++;
        }
        a++;
    }
}
