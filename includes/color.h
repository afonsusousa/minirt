#ifndef MINIRT_COLOR_H
#define MINIRT_COLOR_H

#include "vec3.h"
#include "interval.h"

static inline unsigned int create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}

static inline unsigned int color_to_int(t_color c)
{
    static const t_interval intensity = {0.000, 0.999};

    return create_trgb(
        0,
        (unsigned char)(256 * interval_clamp(intensity, c.x)),
        (unsigned char)(256 * interval_clamp(intensity, c.y)),
        (unsigned char)(256 * interval_clamp(intensity, c.z))
    );
}

#endif
