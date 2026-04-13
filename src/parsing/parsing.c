#include "../../lib/libft/libft.h"
#include "unistd.h"
#include "fcntl.h"
#include <math.h>
#include "../../includes/obj.h"
#include "parsing.h"
#include <stdlib.h>
#include <stdio.h>

bool    parse_format(char **line, t_parsed_obj *obj, int flags)
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


static bool parse_type(t_parsed_obj *obj, t_obj_type type, char **line, int flags)
{
    obj->type = type;
    return (parse_format(line, obj, flags));
}

bool    parse_line(char **line, t_parsed_obj *obj)
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
