/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:20:59 by mpinna-l          #+#    #+#             */
/*   Updated: 2022/09/27 11:22:35 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
