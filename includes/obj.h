//
// Created by afonsusousa on 11/12/25.
//

#ifndef MINIRT_OBJ_H
#define MINIRT_OBJ_H
#include "ray.h"
#include "vec3.h"
#include "stdbool.h"
#include "stddef.h"
#include <stdint.h>

typedef enum
{
    OBJ_AMBIENT = 1,
    OBJ_CAMERA,
    OBJ_LIGHT,
    OBJ_SPHERE,
    OBJ_PLANE,
    OBJ_CYLINDER,
    ERR
} t_obj_type;

typedef enum e_field_type {
    F_VEC3,
    F_DOUBLE,
    F_COLOR,
    F_OPT_MAT,
    F_END
} t_field_type;

typedef enum e_material_type {
    MAT_LIMBERTIAN = 1,
    MAT_METAL,
    MAT_END
} t_material_type;

typedef struct s_format {
    t_field_type type;
    size_t       offset;
    const char   *name;
} t_format;

struct s_hit;
struct s_material;
struct s_camera;

typedef bool (*t_scatter_func)(struct s_camera *c, struct s_hit *record, t_ray *scattered, struct s_material *mat);

typedef struct s_material
{
    t_material_type type;
    t_vec3 color;
    double fuzz;
    t_scatter_func scatter;
} __attribute__((aligned(32))) t_material;

typedef struct s_obj
{
    t_obj_type  type;
    uint32_t    mat_idx;
    
    union {
        struct 
        {
            t_vec3 center;
            double radius;
        } sphere;
        struct 
        {
            t_vec3 pos;
            t_vec3 dir;
        } plane;

        struct {
            t_vec3 pos;
            t_vec3 dir;
            double radius;
            double height;
        } cylinder;

    } shape;
} __attribute__((aligned(32))) t_obj;

typedef struct s_camera
{
    t_vec3  pos;
    t_vec3  dir;
    double  fov;
    
    // rendering variables
    int     image_width;
    int     image_height;
    t_vec3  camera_center;
    t_vec3  pixel_delta_u;
    t_vec3  pixel_delta_v;
    t_vec3  pixel00_loc;
    int     samples_per_pixel;
    double  pixel_samples_scale;
    t_pcg32_random rng; // random state
} __attribute__((aligned(32))) t_camera;

typedef struct s_light
{
    t_vec3 pos;
    double ratio;
    t_vec3 color;
} t_light;

typedef struct s_ambient
{
    double ratio;
    t_vec3 color;
} t_ambient;

typedef struct s_world
{
    t_obj       *objects;
    size_t      num_objects;
    
    t_material  *materials;
    size_t      num_materials;
    
    t_camera    camera;
    t_ambient   ambient;
    t_light     *lights;
    size_t      num_lights;
} __attribute__((aligned(32))) t_world;

#endif //MINIRT_OBJ_H
