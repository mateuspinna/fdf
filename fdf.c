#include "libft/libft.h"
#include "mlx/mlx.h"

typedef struct s_map
{
    int *lines;
    int *columns;
} t_map;

typedef struct  s_data
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}               t_data;

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel /     8));
    *(unsigned int *)dst = color;
}

void creating_window(int **map_array, t_map map_info)
{
    void    *mlx;
    void    *mlx_win;
    t_data  img;
    int     x;
    int     y;

    x = 0;
    y = 0;
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 750, 750, "fdf");
    img.img = mlx_new_image(mlx, 750, 750);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    while (x < *map_info.lines)
    {
        y = 0;
        while (y < *map_info.columns)
        {
            if (map_array[x][y] > 0)
                my_mlx_pixel_put(&img, 30*y, 30*x, 0x00ff0000);
            else
                my_mlx_pixel_put(&img, 30*y, 30*x, 0x0056ffff);
            y++;
        }
        x++;
    }
    mlx_put_image_to_window(mlx, mlx_win, img.img, 50, 50);
    mlx_loop(mlx);

}

int map_lines(char *str)
{
    int     line_counter;
    int     fd;
    char    *line;
    
    line_counter = 0;
    fd = open(str, O_RDONLY);
    if(fd == -1)
    {
        close(fd);
        return (-1);
    }
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        free(line);
        line_counter++;
    }
    close(fd);
    return(line_counter);
}

void    fill_map_array(char *line, t_map map_info, int **map_array)
{
    char        **splitted_line;
    int         i;
    static int  j;

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

int **map_read(char *str, t_map map_info)
{
    int     fd;
    char    *line;
    int     i;
    int     **map_array;

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

void    freeinfo(t_map map_info, int **map_array)
{
    int x;
    int i;

    i = 0;
    x = *map_info.lines;   
    while ( i < x )
    {   
        free(map_array[i]);
        i++;
    }
    free(map_array);
    free (map_info.lines);
    free (map_info.columns);
}

int main (int argc, char **argv)
{
    t_map   map_info;
    int     **map_array;
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
