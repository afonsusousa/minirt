#ifndef MINIRT_COLOR_H
# define MINIRT_COLOR_H

# include "interval.h"
# include "vec3.h"

static inline unsigned int	create_trgb(unsigned char t, unsigned char r,
		unsigned char g, unsigned char b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

static inline double	linear_component(double c)
{
	if (c > 0)
		return (sqrt(c));
	return (0);
}

static inline unsigned int	color_to_int(t_color c)
{
	static const t_interval	intensity = {0.000, 0.999};
	double					r;
	double					g;
	double					b;

	r = linear_component(c.x);
	g = linear_component(c.y);
	b = linear_component(c.z);
	return (create_trgb(0, (unsigned char)(256 * interval_clamp(intensity, r)),
			(unsigned char)(256 * interval_clamp(intensity, g)),
			(unsigned char)(256 * interval_clamp(intensity, b))));
}

#endif
