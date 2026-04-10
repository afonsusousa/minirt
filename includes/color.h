#ifndef MINIRT_COLOR_H
#define MINIRT_COLOR_H

#include "vec3.h"

typedef t_vec3 t_color;

static inline unsigned int create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}

static inline unsigned int color_to_int(t_color c)
{
    return create_trgb(
        0,
        (unsigned char)(255.999 * c.x),
        (unsigned char)(255.999 * c.y),
        (unsigned char)(255.999 * c.z)
    );
}

#endif
