/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scatter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 18:56:04 by amagno-r          #+#    #+#             */
/*   Updated: 2026/04/29 19:16:35 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/color.h"
#include "../includes/vec3.h"
#include "../includes/ray.h"
#include "../includes/obj.h"
#include "../includes/camera.h"
#include "../includes/intersection.h"
#include "../includes/world.h"

bool scatter_lambertian(t_camera *c, t_hit *record, t_ray *scattered, t_material *mat)
{
    t_vec3 scatter_dir;

    (void) mat;
    scatter_dir = v3_add(record->N, random_on_hemisphere(&c->rng, &record->N));
    if(v3_near_zero(scatter_dir))
        scatter_dir = record->N;
    *scattered = (t_ray){record->p, scatter_dir};
    return (true);
}

bool scatter_dielectric(t_camera *c, t_hit *record, t_ray *scattered, t_material *mat)
{
    t_vec3 refracted;
    double refraction_ratio;
    bool cannot_refract;
    t_vec3 reflected;
    (void)c;

    refraction_ratio = record->front_face
        ? (1.0 / mat->refractive_index)
        : mat->refractive_index;
    t_vec3 unit_direction = v3_unit(scattered->direction);
    t_vec3 neg_dir = v3_neg(unit_direction);
    double cos_theta = fmin(v3_dot(&neg_dir, &record->N), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    cannot_refract = refraction_ratio * sin_theta > 1.0;
    if(cannot_refract || v3_reflectance(cos_theta, refraction_ratio) > pcg_range_double(&c->rng, 0.0, 1.0))
    {
        reflected = v3_reflect(unit_direction, record->N);
        *scattered = (t_ray){record->p, reflected};
    }
    else
    {
        refracted = v3_refract(unit_direction, record->N, refraction_ratio);
        *scattered = (t_ray){record->p, refracted};
    }
    return (true);
}

bool scatter_metal(t_camera *c, t_hit *record, t_ray *scattered, t_material *mat)
{
    t_vec3 reflected;
    (void)c;

    reflected = v3_reflect(scattered->direction, record->N); 
    reflected = v3_add(v3_unit(reflected),
                       v3_muls(
                            random_in_unit_sphere(&c->rng),
                            mat->fuzz
                        )
                    );
    *scattered = (t_ray){record->p, reflected};
    return (v3_dot(&scattered->direction, &record->N) > 0);
}

bool scatter_default(t_camera *c, t_hit *record, t_ray *scattered, t_material *mat)
{
    t_vec3 scatter_dir;
    (void) mat;

    scatter_dir = random_on_hemisphere(&c->rng, &record->N);
    *scattered = (t_ray){record->p, scatter_dir};
    return (false);
}

void assign_material_scatter_funcs(t_world *w)
{
    size_t i;

    i = 0;
    while (i < w->num_materials)
    {
        if (w->materials[i].type == MAT_LIMBERTIAN)
            w->materials[i].scatter = scatter_lambertian;
        else if (w->materials[i].type == MAT_METAL)
            w->materials[i].scatter = scatter_metal;
        else if (w->materials[i].type == MAT_DIELECTRIC)
            w->materials[i].scatter = scatter_dielectric;
        else
            w->materials[i].scatter = scatter_default;
        i++;
    }
}
