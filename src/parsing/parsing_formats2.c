#include "../../includes/obj.h"
#include "parsing.h"
#include <stddef.h>

const t_format  *get_light_fmt(void)
{
    static const t_format fmt[] = {
    {F_VEC3, offsetof(t_light, pos), "pos"},
    {F_DOUBLE, offsetof(t_light, ratio), "ratio"},
    {F_COLOR, offsetof(t_light, color), "color"},
    {F_END, 0, NULL}
    };

    return (fmt);
}
