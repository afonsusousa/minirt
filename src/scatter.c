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

// The incoming ray direction is pre-stored inside scattered->direction to save stack memory and param bloat
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
        else
            w->materials[i].scatter = scatter_default;
        i++;
    }
}
