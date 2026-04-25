#include "../lib/minilibx-linux/mlx.h"
#include "../includes/mlx_mitm.h"
#include "../includes/color.h"
#include "../includes/vec3.h"
#include "../includes/ray.h"
#include "../includes/obj.h"
#include "../includes/camera.h"
#include "../includes/intersection.h"
#include "../includes/interval.h"
#include "../includes/world.h"
#include <stdio.h>

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

t_vec3 ray_color(t_camera *c, t_ray *r, t_world *world, size_t bounce)
{
    if (bounce <= 0)
        return (vec3(0, 0, 0));

    t_hit record;
    t_hit closest_record;
    bool hit_anything = false;
    double closest_so_far = INFINITY;
    t_material *closest_mat = NULL;

    for (size_t i = 0; i < world->num_objects; i++)
    {
        if (hit(&world->objects[i], r, (t_interval){0.001, closest_so_far}, &record))
        {
            hit_anything = true;
            closest_so_far = record.t;
            closest_record = record;
            closest_mat = &world->materials[world->objects[i].mat_idx];
        }
    }

    if (hit_anything)
    {
        t_ray scattered;
        t_vec3 attenuation = closest_mat->scatter(r, &closest_record, &scattered, closest_mat);
        return (v3_mul(ray_color(c, &scattered, world, bounce - 1), attenuation));
    }

    t_vec3 unit_direction = v3_unit(r->direction);
    double a = 0.5 * (unit_direction.y + 1.0);
    // Sky gradient: white to blue
    return (v3_add(
        v3_muls(vec3(1.0, 1.0, 1.0), 1.0 - a),
        v3_muls(vec3(0.5, 0.7, 1.0), a)));
}


void my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color)
{
    char *dst;
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void assign_material_scatter_funcs(t_world *w)
{
    for (size_t i = 0; i < w->num_materials; i++)
    {
        if (w->materials[i].type == MAT_LIMBERTIAN)
            w->materials[i].scatter = scatter_lambertian;
        else if (w->materials[i].type == MAT_METAL)
            w->materials[i].scatter = scatter_metal;
        else
            w->materials[i].scatter = scatter_default;
    }
}

int main(void)
{
    void *mlx;
    void *mlx_win;
    t_data img;
    t_world w;

    parse_file(&w, "exemplo2.3d");

    for (size_t i = 0; i < w.num_objects; i++)
    {
        if (w.objects[i].type == OBJ_SPHERE)
        {
            size_t mat_id = w.objects[i].mat_idx;
            w.materials[mat_id].type = MAT_METAL;
            if (mat_id == 0 || mat_id == 3)
                w.materials[mat_id].type = MAT_LIMBERTIAN;
        }
    }

    assign_material_scatter_funcs(&w);

    init_camera(&w.camera, 1080, 16.0 / 9.0);
    img.width = w.camera.image_width;
    img.height = w.camera.image_height;

    printf("w.camera.pixel00_loc: %f %f %f\n", w.camera.pixel00_loc.x, w.camera.pixel00_loc.y, w.camera.pixel00_loc.z);

    printf("w.camera.pixel00_loc: %f %f %f\n", w.camera.pixel00_loc.x, w.camera.pixel00_loc.y, w.camera.pixel00_loc.z);

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, img.width, img.height, "Hello world!");
    img.img = mlx_new_image(mlx, img.width, img.height);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);

    for (int y = 0; y < img.height; y++)
    {
        for (int x = 0; x < img.width; x++)
        {
            t_color pixel_color = vec3(0, 0, 0);
            for (int sample = 0; sample < w.camera.samples_per_pixel; sample++)
            {
                t_ray ray = get_ray(&w.camera, x, y);
                t_color sample_color = ray_color(&w.camera, &ray, &w, 50);
                v3_add_mut(&pixel_color, &sample_color);
            }
            v3_muls_mut(&pixel_color, w.camera.pixel_samples_scale);
            my_mlx_pixel_put(&img, x, y, color_to_int(pixel_color));
        }
    }

    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
}
