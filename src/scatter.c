/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scatter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 18:56:04 by amagno-r          #+#    #+#             */
/*   Updated: 2026/04/25 18:56:04 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/color.h"
#include "../includes/vec3.h"
#include "../includes/ray.h"
#include "../includes/obj.h"
#include "../includes/camera.h"
#include "../includes/intersection.h"
#include "../includes/world.h"

t_vec3 scatter_lambertian(t_ray *r, t_hit *record, t_ray *scattered, t_material *mat)
{
    t_vec3 scatter_dir;

    scatter_dir = v3_add(record->N, random_on_hemisphere(&((t_camera *)r)->rng, &record->N));
    if(v3_near_zero(scatter_dir))
        scatter_dir = record->N;
    *scattered = (t_ray){record->p, scatter_dir};
    return (mat->color);
}

t_vec3 scatter_metal(t_ray *r, t_hit *record, t_ray *scattered, t_material *mat)
{
    t_vec3 reflected;

    reflected = v3_reflect(r->direction, record->N); 
    *scattered = (t_ray){record->p, reflected};
    return (mat->color); // Or modify somehow based on metal properties
}

t_vec3 scatter_default(t_ray *r, t_hit *record, t_ray *scattered, t_material *mat)
{
    t_vec3 scatter_dir;

    scatter_dir = random_on_hemisphere(&((t_camera *)r)->rng, &record->N);
    *scattered = (t_ray){record->p, scatter_dir};
    return (v3_muls(mat->color, 0.5)); // Arbitrary default fallback handling
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
