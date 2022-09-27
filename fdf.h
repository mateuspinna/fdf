/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:41:13 by mpinna-l          #+#    #+#             */
/*   Updated: 2022/09/27 10:38:17 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "mlx/mlx.h"

typedef struct s_map
{
	int	*lines;
	int	*columns;
}				t_map;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		l_length;
	int		endian;
}				t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*mlx_win;
}				t_vars;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		close_win_esc(int keycode, t_vars *vars);
int		close_win_x(t_vars *vars);
void	creating_window(int **map_array, t_map map_info);
void	fill_image(t_vars vars, t_data *img, t_map map_info, int **map_array);

#endif
