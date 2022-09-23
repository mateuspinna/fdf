#include "libft/libft.h"

typedef struct s_map
{
    int **map_array;
    int *lines;
    int *columns;
} t_map;

int map_lines(char *str)
{
    int     line_counter;
    int     fd;
    
    line_counter = 0;
    fd = open(str, O_RDONLY);
    while (get_next_line(fd))
        line_counter++;
    return(line_counter);
}

void    fill_map_array(char *line, int *map_array, int *columns)
{
    char    **splitted_line;
    int     i;

    i = 0;
    splitted_line = ft_split(line, ' ');
    while (splitted_line[i])
        i++;
    if (!(*columns))
        *columns = i;
    free(splitted_line[i--]);
    map_array = malloc(i * sizeof(int));
    while (i)
    {
        map_array[i] = ft_atoi(splitted_line[i]); 
        free(splitted_line[i--]);
    }
    free(splitted_line);
    free(line);
}

void    map_read(char *str, t_map map_info)
{
    int     fd;
    char    *line;
    int     i;

    i = 0;
    *map_info.lines = map_lines(str);
    fd = open(str, O_RDONLY);
    if (fd == -1 || *map_info.lines == 0)
        exit(1);
    map_info.map_array = malloc((*map_info.lines) * sizeof(int *));
    while (i < (*map_info.lines))
    {
        line = get_next_line(fd);
        fill_map_array(line, map_info.map_array[i++], map_info.columns);
    }
    close(fd);
}

int main (int argc, char **argv)
{
    t_map map_info;

    if (argc == 2)
    {
        map_info.lines = malloc(sizeof(int)); 
        map_info.columns = malloc(sizeof(int)); 
        ft_bzero(&(*map_info.lines), sizeof (int));
        ft_bzero(&(*map_info.columns), sizeof (int));
        map_read(argv[1], map_info);
        ft_printf("%i\n", *map_info.lines);
        ft_printf("%i\n", *map_info.columns);
    }
}
