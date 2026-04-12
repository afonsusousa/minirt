#include "../../lib/libft/libft.h"
#include "unistd.h"
#include "fcntl.h"
#include <math.h>
#include "../../includes/obj.h"
#include "parsing.h"
#include <stdlib.h>
#include <stdio.h>

bool  parse_double(char **line, double *d)
{
    double integer;
    double decimal;

    if (!ft_isdigit(**line) && **line != '-' && **line != '+')
        return (false);
    integer = ft_atoi((const char *)*line);
    *line += magnitude(integer) + (integer < 0 || **line == '+' || **line == '-');
    if (**line != '.')
    {
        *d = (double)integer;
        return (true);
    }
    (*line)++;
    if (!ft_isdigit(**line))
        return (false);
    decimal = ft_atoi((const char *) *line);
    *d = (double) integer 
        + (((integer < 0) * -1) + (integer >= 0)) 
        * (decimal / pow(10.0, (double) magnitude(decimal)));
    *line += magnitude(decimal);
    return (true);
}

//maybe move the division upstream
bool    parse_vec3_uchar(char **line, t_vec3    *vec)
{
    unsigned char x;
    unsigned char y;
    unsigned char z;

    if (!ft_isdigit(**line))
        return (false);
    x = ft_atoi((const char *)*line);
    *line += magnitude(x);
    if (**line != ',')
        return (false);
    (*line)++;
    if (!ft_isdigit(**line))
        return (false);
    y = ft_atoi((const char *)*line);
    *line += magnitude(y);
    if (**line != ',')
        return (false);
    (*line)++;
    if (!ft_isdigit(**line))
        return (false);
    z = ft_atoi((const char *)*line);
    *line += magnitude(z);
    *vec = vec3(x / 255.0, y / 255.0, z / 255.0);
    return (true);
}

bool    parse_vec3_double(char **line, t_vec3   *vec)
{
    double  x;
    double  y;
    double  z;

    if (!parse_double(line, &x) || **line != ',')
        return (false);
    (*line)++;
    if (!parse_double(line, &y) || **line != ',')
        return (false);
    (*line)++;
    if (!parse_double(line, &z))
        return (false);
    *vec = vec3(x, y, z);
    return (true);
}

bool    parse_format(char **line, t_obj *obj, int flags)
{
    if ((flags & F_POS) && (!skip(line, ft_isspace)
            || !parse_vec3_double(line, &obj->pos)))
        return (false);
    if ((flags & F_DIR) && (!skip(line, ft_isspace)
            || !parse_vec3_double(line, &obj->dir)))
        return (false);
    if ((flags & F_RATIO) && (!skip(line, ft_isspace)
            || !parse_double(line, &obj->ratio)))
        return (false);
    if ((flags & F_FOV) && (!skip(line, ft_isspace)
            || !parse_double(line, &obj->fov)))
        return (false);
    if ((flags & F_SIZE) && (!skip(line, ft_isspace)
            || !parse_double(line, &obj->radius)))
        return (false);
    if ((flags & F_HEIGHT) && (!skip(line, ft_isspace)
            || !parse_double(line, &obj->height)))
        return (false);
    if ((flags & F_COLOR) && (!skip(line, ft_isspace)
            || !parse_vec3_uchar(line, &obj->color)))
        return (false);
    return (true);
}


static bool parse_type(t_obj *obj, t_obj_type type, char **line, int flags)
{
    obj->type = type;
    return (parse_format(line, obj, flags));
}

bool    parse_line(char **line, t_obj *obj)
{
    skip(line, ft_isspace);
    if (**line == '\0' || **line == '\n')
    {
        obj->type = ERR;
        return (true);
    }
    if (match_id(line, "sp"))
        return (parse_type(obj, OBJ_SPHERE, line, F_FMT_SPHERE));
    if (match_id(line, "pl"))
        return (parse_type(obj, OBJ_PLANE, line, F_FMT_PLANE));
    if (match_id(line, "cy"))
        return (parse_type(obj, OBJ_CYLINDER, line, F_FMT_CYLINDER));
    if (match_id(line, "A"))
        return (parse_type(obj, OBJ_AMBIENT, line, F_FMT_AMBIENT));
    if (match_id(line, "C"))
        return (parse_type(obj, OBJ_CAMERA, line, F_FMT_CAMERA));
    if (match_id(line, "L"))
        return (parse_type(obj, OBJ_LIGHT, line, F_FMT_LIGHT));
    return (false);
}

//maybe detect errors here, also error handling
t_world *parse_file(t_world *wrld, char *path)
{
    int     fd;
    t_obj   obj;
    size_t  i;
    char    *line;
    char    *current;

    wrld->size = 0;
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (NULL);
    while ((line = get_next_line(fd)))
    {
        wrld->size++;
        free(line);
    }
    close(fd);
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (NULL);
    wrld->map = ft_calloc(wrld->size, sizeof(t_obj));
    i = 0;
    while (i < wrld->size)
    {
        line = get_next_line(fd);
        current = line;
        if (!parse_line(&current, &obj))
        {
            syntax_error(path, i + 1, line, current);
            free(line);
            return (NULL);
        }
        wrld->map[i++] = obj;
        free(line);
    }
    return (wrld);
}