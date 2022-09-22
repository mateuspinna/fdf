#include "libft/libft.h"

int count_map_line(char *str)
{
    int fd;
    int i;

    i = 0;
    fd = open(str, O_RDONLY);
    while (get_next_line(fd) && fd != -1)
        i++;
    close(fd);
    if (!i)
        exit(1);
    return (i);
}

int **map_array(char **lines, int map_lines)
{
    int     x;
    int     y;
    char    **temp;
    int     **array;
    int     count;
    
    array = malloc (map_lines * sizeof (int *));
    y = 0;
    while (map_lines--)
    {
        x = 0;
        count = 0;
        temp = ft_split(lines[y], ' ');
        while (temp[x++])
            count++;
        x = count;
        array[y] = malloc (count * sizeof (int));
        while (count)
            array[y][--count] = ft_atoi (temp[--x]);
        y++;
        // LEMBRAR DE DAR FREE NO TEMP //
    }
    return (array); 
} 


int main (int argc, char **argv)
{
    int     fd;
    char    **lines;
    int     i;
    int     **map;

    if (argc == 2)
    {
        i = 0;
        fd = open(argv[1] , O_RDONLY);
        lines = malloc(count_map_line(argv[1]) * sizeof (char *)); 
        while (1 && fd != -1)
        {
            lines[i] = get_next_line(fd);
            if (!lines[i++])
                break;
        }
        // LEMBRAR DE DAR FREE EM LINES //
        map = map_array(lines, count_map_line(argv[1]));
    }
}
