#include "../lib/libft/libft.h"
#include "unistd.h"
#include "fcntl.h"
#include <math.h>
#include "obj.h"
#include <stdlib.h>
#include <stdio.h>

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

bool    ft_isspace(char c)
{
    return (c == ' ' || (c >= 9 && c <= 13));
}


bool    skip(char **s, bool (*predicate)(char))
{
    bool ret;

    ret = false;
    while (**s && predicate(**s))
    {
        (*s)++;
        ret = true;
    }
    return (ret);
}

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

bool    parse_sphere(char **line, t_obj *obj)
{
    *line += 2;
    if (!skip(line, ft_isspace))
        return (false);
    if (!parse_vec3_double(line, &obj->pos))
        return (false);
    if (!skip(line, ft_isspace))
        return (false);
    if (!parse_double(line, &obj->data.sphere.radius))
        return (false);
    if (!skip(line, ft_isspace))
        return (false);
    if (!parse_vec3_uchar(line, &obj->color))
        return (false);
    obj->type = OBJ_SPHERE;
    return (true);
}

bool    parse_line(char **line, t_obj *obj)
{
    skip(line, ft_isspace);
    if (**line == '\0' || **line == '\n')
    {
        obj->type = ERR; // or another type representing "empty line" to safely skip it
        return (true);
    }
    if (ft_strncmp(*line, "sp", 2) == 0)
        return (parse_sphere(line, obj));
    return (false);
}

void    syntax_error(const char *file, int line, const char *start, const char *current)
{
    int offset;
    int i;
    int len;

    offset = current - start;
    printf("%s:%d:%d: error: syntax error\n", file, line, offset + 1);
    printf("%s", start);
    len = ft_strlen(start);
    if (len == 0 || start[len - 1] != '\n')
        printf("\n");
    i = 0;
    while (i < offset)
    {
        if (start[i] == '\t')
            printf("\t");
        else
            printf(" ");
        i++;
    }
    printf("^\n");
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