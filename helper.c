/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 20:21:53 by jomunoz           #+#    #+#             */
/*   Updated: 2025/07/27 19:59:15 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int find_biggest(t_fdf *fdf)
{
    int x;
    int y;
    int biggest;
    
    x = 0;
    y = 0;
    biggest = fdf->map.values[0][0];
    while (y < fdf->map.height)
    {
        x = 0;
        while (x < fdf->map.width)
        {
            if (fdf->map.values[y][x] > biggest)
                biggest = fdf->map.values[y][x];
            x++;
        }
        y++;
    }
    return (biggest);
}

int find_smallest(t_fdf *fdf)
{
    int x;
    int y;
    int smallest;
    
    x = 0;
    y = 0;
    smallest = INT_MAX;
    while (y < fdf->map.height)
    {
        x = 0;
        while (x < fdf->map.width)
        {
            if (fdf->map.values[y][x] < smallest)
                smallest = fdf->map.values[y][x];
            x++;
        }
        y++;
    }
    return (smallest);
}

int return_smallest(int a, int  b)
{
    if (a < b)
        return (a);
    else
        return (b);
}

void    free_every_row(t_fdf *fdf, int allocated_rows)
{
    int a;

    a = 0;
    while (a < allocated_rows)
    {
        free(fdf->map.values[a]);
        a++;
    }
    free(fdf->map.values);
    free(&fdf->map);
}
