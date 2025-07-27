/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 22:18:26 by jomunoz           #+#    #+#             */
/*   Updated: 2025/07/27 20:51:02 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window(void *param)
{
	(void)param;
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

static  int key_handler(int keycode, void *param)
{
    t_fdf *fdf;
    
    fdf = (t_fdf *)param;
    printf("Key pressed with keycode: %d\n", keycode);
    if (keycode == KEY_P) 
    {
        window_to_black(fdf->mlx.img_addr, fdf->mlx.line_len * WIN_HEIGHT);
        fdf->map.mode = MODE_ORTHOGRAPHIC;
        project_orthographic(fdf);
    }
    if (keycode == KEY_I) 
    {
        window_to_black(fdf->mlx.img_addr, fdf->mlx.line_len * WIN_HEIGHT);
        fdf->map.mode = MODE_ISOMETRIC;
        project_isometric(fdf);
    }
    if (keycode == KEY_E) 
    {
        window_to_black(fdf->mlx.img_addr, fdf->mlx.line_len * WIN_HEIGHT);
        fdf->set.change_elevation += 1;
        if (fdf->map.mode == MODE_ISOMETRIC)
            project_isometric(fdf);
        else
            project_orthographic(fdf); 
    }
    if (keycode == KEY_R) 
    {
        window_to_black(fdf->mlx.img_addr, fdf->mlx.line_len * WIN_HEIGHT);
        fdf->set.change_elevation -= 1;
        if (fdf->map.mode == MODE_ISOMETRIC)
            project_isometric(fdf);
        else
            project_orthographic(fdf); 
    }
    if (keycode == KEY_W) 
    {
        window_to_black(fdf->mlx.img_addr, fdf->mlx.line_len * WIN_HEIGHT);
        fdf->set.y_offset -= 25;
        if (fdf->map.mode == MODE_ISOMETRIC)
            project_isometric(fdf);
        else
            project_orthographic(fdf); 
    }
    if (keycode == KEY_S) 
    {
        window_to_black(fdf->mlx.img_addr, fdf->mlx.line_len * WIN_HEIGHT);
        fdf->set.y_offset += 25;
        if (fdf->map.mode == MODE_ISOMETRIC)
            project_isometric(fdf);
        else
            project_orthographic(fdf); 
    }
    if (keycode == KEY_A) 
    {
        window_to_black(fdf->mlx.img_addr, fdf->mlx.line_len * WIN_HEIGHT);
        fdf->set.x_offset -= 25;
        if (fdf->map.mode == MODE_ISOMETRIC)
            project_isometric(fdf);
        else
            project_orthographic(fdf); 
    }
    if (keycode == KEY_D) 
    {
        window_to_black(fdf->mlx.img_addr, fdf->mlx.line_len * WIN_HEIGHT);
        fdf->set.x_offset += 25;
        if (fdf->map.mode == MODE_ISOMETRIC)
            project_isometric(fdf);
        else
            project_orthographic(fdf); 
    }
    if (keycode == KEY_PLUS) 
    {
        window_to_black(fdf->mlx.img_addr, fdf->mlx.line_len * WIN_HEIGHT);
        fdf->set.pixel_size += 3;
        if (fdf->map.mode == MODE_ISOMETRIC)
            project_isometric(fdf);
        else
            project_orthographic(fdf); 
    }
    if (keycode == KEY_MINUS) 
    {
        window_to_black(fdf->mlx.img_addr, fdf->mlx.line_len * WIN_HEIGHT);
        if (fdf->set.pixel_size > 4)
            fdf->set.pixel_size -= 3;
        if (fdf->map.mode == MODE_ISOMETRIC)
            project_isometric(fdf);
        else
            project_orthographic(fdf); 
    }
    if (keycode == KEY_UP) 
    {
        window_to_black(fdf->mlx.img_addr, fdf->mlx.line_len * WIN_HEIGHT);
    }
    if (keycode == KEY_DOWN) 
    {
        window_to_black(fdf->mlx.img_addr, fdf->mlx.line_len * WIN_HEIGHT);
    }
    if (keycode == KEY_LEFT) 
    {
        window_to_black(fdf->mlx.img_addr, fdf->mlx.line_len * WIN_HEIGHT);
        fdf->set.rotation_x -= 0.05;
        // printf("Key press detected, new rotation_x: %.3f\n", fdf->set.rotation_x);
        project_isometric_rot(fdf);
    }
    if (keycode == KEY_RIGHT) 
    {
        window_to_black(fdf->mlx.img_addr, fdf->mlx.line_len * WIN_HEIGHT);
    }
    return (0);
}

int main(int argc, char *argv[])
{
    static t_fdf   fdf;
    int     fd;
    
    if (argc != 2)
    {
        write(2, "Error, invalid arguments\n", 26);
        exit(1);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file:");
        exit(1);
    }
    get_int_map(&fdf, get_map_with_style(fd, 0));
    assign_map_projected(&fdf);
    assign_mlx_functions(&fdf);
    assign_map_configurations(&fdf);
    assign_map_projected_rot(&fdf);

    
    mlx_hook(fdf.mlx.win_ptr, 17, 0, close_window, NULL);
  
    mlx_key_hook(fdf.mlx.win_ptr, key_handler, &fdf);
    
    project_isometric(&fdf);

    mlx_loop(fdf.mlx.mlx_ptr);
    
    mlx_destroy_image(fdf.mlx.mlx_ptr, fdf.mlx.img_ptr);

    // see randomizer of math library
    
    //  guia do DDA
    // Handle key events	mlx_key_hook(win, func, param)	Registers func to handle keyboard input
    // General events	mlx_hook(win, event, mask, func, param)	Low level event hook

    // Robust FdF projects always compute scaling and centering based on both the map and window size, ensuring the result is visible and well-placed, 
    // regardless of how you configure your mlx_new_window or mlx_new_image. 

    // protect against a file that doesn t exist
    // protect against chmod 000

    // implement key for elevation

    // gcc wrong
    
}








/* 
int main(void)
{
    int fd;
    char **map;
    char *temp;
    int     a;
    
    fd = open("10-2.fdf", O_RDONLY);
    map = get_map_with_style(fd, 0);
    while(map && *map)
    {
        printf("%s", *map);
        map++;
        a++;
    }
} */

// while(map[a])
// {
//     b = 0;
//     while(b < 12)
//     {
//         printf("%d ", map[a][b]);
//         b++;
//     }
//     printf("\n");
//     a++;
// }