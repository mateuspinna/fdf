#include "libft/libft.h"

typedef struct s_map
{
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

void    fill_map_array(char *line, t_map map_info, int j, int **map_array)
{
    char    **splitted_line;
    int     i;

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
    while (i < *map_info.lines)
    {
        line = get_next_line(fd);
        fill_map_array(line, map_info, i++, map_array);
    }
    close(fd);
    return (map_array);
}

void    freeinfo(t_map map_info, int **map_array)
{
    int x;
    int i;
    int j;

    i = 0;
    x = *map_info.lines;   
    while ( i < x )
    {   
        j = 0;
        while (j < *map_info.columns)
            ft_printf("%i ", (map_array[i][j++]));
        free(map_array[i]);
        ft_printf("\n");
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
        freeinfo(map_info, map_array);
    }
}
