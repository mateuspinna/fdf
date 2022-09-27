/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:20:59 by mpinna-l          #+#    #+#             */
/*   Updated: 2022/09/27 09:57:29 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "mlx/mlx.h"
#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->l_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	close_win_esc(int keycode, t_vars *vars)
{
	(void)keycode;
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->mlx_win);
		exit(1);
	}
	return (0);
}

int	close_win_x(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	exit(1);
	return (0);
}

void	creating_window(int **map_array, t_map map_info)
{
	t_vars	vars;
	t_data	img;
	int		x;
	int		y;

	x = 0;
	y = 0;
	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, 750, 750, "fdf");
	img.img = mlx_new_image(vars.mlx, 750, 750);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.l_length, &img.endian);
	while (x < *map_info.lines)
	{
		y = 0;
		while (y < *map_info.columns)
		{
			if (map_array[x][y] > 0)
				my_mlx_pixel_put(&img, 30 * y, 30 * x, 0x00ff0000);
			else if (map_array[x][y] < 0)
				my_mlx_pixel_put(&img, 30 * y, 30 * x, 0x0000ff88);
			else
				my_mlx_pixel_put(&img, 30 * y, 30 * x, 0x00FFFFFF);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(vars.mlx, vars.mlx_win, img.img, 50, 50);
	mlx_hook(vars.mlx_win, 2, 0, close_win_esc, &vars);
	mlx_hook(vars.mlx_win, 17, 0, close_win_x, &vars);
	mlx_loop(vars.mlx);
}

int	map_lines(char *str)
{
	int		line_counter;
	int		fd;
	char	*line;

	line_counter = 0;
	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		return (-1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		line_counter++;
	}
	close(fd);
	return (line_counter);
}

void	fill_map_array(char *line, t_map map_info, int **map_array)
{
	char		**splitted_line;
	int			i;
	static int	j;

	i = 0;
	splitted_line = ft_split(line, ' ');
	while (splitted_line[i])
		i++;
	if (!(*map_info.columns))
		*map_info.columns = i;
	free(splitted_line[i--]);
	map_array[j] = malloc(i * sizeof(int));
	while (i)
	{
		map_array[j][i] = ft_atoi(splitted_line[i]);
		free(splitted_line[i--]);
	}
	j++;
	free(splitted_line);
	free(line);
}

int	**map_read(char *str, t_map map_info)
{
	int		fd;
	char	*line;
	int		i;
	int		**map_array;

	i = 0;
	*map_info.lines = map_lines(str);
	fd = open(str, O_RDONLY);
	if (fd == -1 || *map_info.lines == 0)
		exit(1);
	map_array = malloc((*map_info.lines) * sizeof(int *));
	if (!map_array)
		exit(1);
	while (i++ < *map_info.lines)
	{
		line = get_next_line(fd);
		fill_map_array(line, map_info, map_array);
	}
	close(fd);
	return (map_array);
}

void	freeinfo(t_map map_info, int **map_array)
{
	int	x;
	int	i;

	i = 0;
	x = *map_info.lines;
	while (i < x)
	{
		free(map_array[i]);
		i++;
	}
	free(map_array);
	free(map_info.lines);
	free (map_info.columns);
}

int	main(int argc, char **argv)
{
	t_map	map_info;
	int		**map_array;

	if (argc == 2)
	{
		map_info.lines = malloc(sizeof(int));
		map_info.columns = malloc(sizeof(int));
		ft_bzero(&(*map_info.lines), sizeof (int));
		ft_bzero(&(*map_info.columns), sizeof (int));
		map_array = map_read(argv[1], map_info);
		creating_window(map_array, map_info);
		freeinfo(map_info, map_array);
	}
}
