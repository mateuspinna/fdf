/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:22:26 by mpinna-l          #+#    #+#             */
/*   Updated: 2022/09/27 10:35:04 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->l_length + x * (data->bpp / 8));
    *(unsigned int *)dst = color;
}

int close_win_esc(int keycode, t_vars *vars)
{
    (void)keycode;
    if (keycode == 53)
    {
        mlx_destroy_window(vars->mlx, vars->mlx_win);
        exit(1);
    }
    return (0);
}

int close_win_x(t_vars *vars)
{
    mlx_destroy_window(vars->mlx, vars->mlx_win);
    exit(1);
    return (0);
}

void	fill_image(t_vars vars, t_data *img, t_map map_info, int **map_array)
{
	int	x;
	int	y;

	x = 0;
	img->img = mlx_new_image(vars.mlx, 750, 750);
    img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->l_length, &img->endian);
    while (x < *map_info.lines)
    {
        y = 0;
        while (y < *map_info.columns)
        {
            if (map_array[x][y] > 0)
                my_mlx_pixel_put(img, 30 * y, 30 * x, 0x00ff0000);
            else if (map_array[x][y] < 0)
                my_mlx_pixel_put(img, 30 * y, 30 * x, 0x0000ff88);
            else
                my_mlx_pixel_put(img, 30 * y, 30 * x, 0x00FFFFFF);
            y++;
        }
        x++;
    }

}

void    creating_window(int **map_array, t_map map_info)
{
    t_vars  vars;
    t_data  img;

    vars.mlx = mlx_init();
    vars.mlx_win = mlx_new_window(vars.mlx, 750, 750, "fdf");
	fill_image(vars, &img, map_info, map_array);
    mlx_put_image_to_window(vars.mlx, vars.mlx_win, img.img, 50, 50);
    mlx_hook(vars.mlx_win, 2, 0, close_win_esc, &vars);
    mlx_hook(vars.mlx_win, 17, 0, close_win_x, &vars);
    mlx_loop(vars.mlx);
}

