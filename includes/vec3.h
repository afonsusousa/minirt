//
// Created by afonsusousa on 11/9/25.
//

#ifndef MINIRT_VEC3_H
# define MINIRT_VEC3_H

# include <math.h>
# include <stdint.h>

typedef union s_vec3
{
	struct
	{
		double			x;
		double			y;
		double			z;
		double			w;
	};
	double				e[4];
}						t_vec3;

typedef t_vec3			t_point;
typedef t_vec3			t_color;

# define BASICALLY_ZERO 1e-160

/* function prototypes (implementations moved to .c files) */

t_vec3	vec3(double x, double y, double z);

/* pure functions */

t_vec3	v3_add(t_vec3 a, t_vec3 b);
t_vec3	v3_sub(t_vec3 a, t_vec3 b);
t_vec3	v3_mul(t_vec3 a, t_vec3 b);
t_vec3	v3_sq(t_vec3 a);

t_vec3	v3_muls(t_vec3 vec, double t);
t_vec3	v3_smul(double t, t_vec3 vec);
t_vec3	v3_divs(t_vec3 vec, double t);
t_vec3	v3_neg(t_vec3 vec);
t_vec3	v3_reflect(t_vec3 v, t_vec3 n);

double	v3_dot(const t_vec3 *a, const t_vec3 *b);
double	v3_len_sq(t_vec3 vec);

t_vec3	v3_refract(t_vec3 v, t_vec3 n, double ri);
double	v3_reflectance(double cosine, double ref_idx);

t_vec3	v3_cross(t_vec3 a, t_vec3 b);
double	v3_len(t_vec3 vec);
t_vec3	v3_unit(t_vec3 vec);
void	v3_unit_mut(t_vec3 *dest);
int	v3_near_zero(t_vec3 vec);

#endif // MINIRT_VEC3_H
