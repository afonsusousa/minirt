#include "../lib/libft/libft.h"
#include "unistd.h"
#include "fcntl.h"
#include <math.h>
#include "obj.h"
#include <stdlib.h>

#define BUFFER_SIZE 256

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE];
    static int buffer_pos;
    static int buffer_read;
    char *line;
    int i = 0;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

    line = malloc(70000);
    if (!line)
        return (NULL);

    while (1)
    {
        if (buffer_pos >= buffer_read)
        {
            buffer_read = read(fd, buffer, BUFFER_SIZE);
            buffer_pos = 0;
            if (buffer_read <= 0)
                break;
        }
        line[i++] = buffer[buffer_pos++];
        if (line[i - 1] == '\n')
            break;
    }

    line[i] = '\0';

    if (i == 0)
    {
        free(line);
        return (NULL);
    }

    return (line);
}

void	free_until_null(char ***str_v)
{
	size_t	i;

	i = 0;
	if (!*str_v)
		return ;
	while ((*str_v)[i])
		free((*str_v)[i++]);
	free(*str_v);
	*str_v = NULL;
}

static size_t ft_count (char **str)
{
    size_t count;

    count = 0;
    while (str && *str++)
        count++;
    return (count);   
}

static size_t  magnitude(int n)
{
    size_t mag;

    if (!n)
        return (1);
    mag = 0;
    while (n != 0)
    {
        mag++;
        n /= 10;
    }
    return (mag);
}


double  ft_atod(const char *nbr)
{
    double integer;
    double decimal;

    integer = ft_atoi(nbr);
    nbr += magnitude(integer) + 1;
    // o wallace tem medo de dois pontos..
    while (*nbr && !ft_isdigit(*nbr))
        nbr++;
    decimal = ft_atoi(nbr);
    return ((double) integer 
        + (((integer < 0) * -1) + integer >= 0) 
        * (decimal / pow(10.0, (double) magnitude(decimal))));
}

//TODO: check coords FULL integrity
// sp 0.0,0.0,20.6 12.6 10,0,255
void    parse_sphere(char **params, t_obj *obj)
{
    char    **coords;
    char    **colors;
    
    obj->type = ERR;
    if (ft_count(params) != 3)
        return ;
    coords = ft_split(params[0], ',');
   if (ft_count(coords) != 3)
        return (free(coords));
    obj->pos = vec3(
        ft_atod(coords[0]),
        ft_atod(coords[1]),
        ft_atod(coords[2])
    ); 
    obj->data.sphere.radius = ft_atod(params[1]);
    colors = ft_split(params[2], ',');
    if (ft_count(colors) != 3)
        return (free(coords), free(colors)); 
    obj->color = vec3(
        ft_atod(colors[0]) / 255.0,
        ft_atod(colors[1]) / 255.0,
        ft_atod(colors[2]) / 255.0
    );
    obj->type = OBJ_SPHERE;
}

// sets obj-type to error if the parsing fails
t_obj   *parse_line(char *line, t_obj *obj)
{
    char **params;

    params = ft_split(line, ' ');
    if (!params)
        return (NULL);    
    if (ft_strncmp(params[0], "sp", 2) == 0)
        parse_sphere(&params[1], obj);
    free_until_null(&params);
    return (obj);
}

//maybe detect errors here, also error handling
t_world *parse_file(t_world *wrld, char *path)
{
    int     fd;
    t_obj   obj;
    size_t  i;

    wrld->size = 0;
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (NULL);
    while (get_next_line(fd))
        wrld->size++;
    close(fd);
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (NULL);
    wrld->map = ft_calloc(wrld->size, sizeof(t_obj));
    i = 0;
    while (i < wrld->size)
    {
        parse_line(get_next_line(fd), &obj);
        if (obj.type == ERR)
            break ;
        wrld->map[i++] = obj;
    }
    return (wrld);
}