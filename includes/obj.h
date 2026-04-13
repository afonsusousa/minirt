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

# define F_POS    (1 << 0)
# define F_DIR    (1 << 1)
# define F_RATIO  (1 << 2)
# define F_FOV    (1 << 3)
# define F_SIZE   (1 << 4)
# define F_HEIGHT (1 << 5)
# define F_COLOR  (1 << 6)

# define F_FMT_SPHERE   (F_POS | F_SIZE | F_COLOR)
# define F_FMT_PLANE    (F_POS | F_DIR | F_COLOR)
# define F_FMT_CYLINDER (F_POS | F_DIR | F_SIZE | F_HEIGHT | F_COLOR)
# define F_FMT_AMBIENT  (F_RATIO | F_COLOR)
# define F_FMT_CAMERA   (F_POS | F_DIR | F_FOV)
# define F_FMT_LIGHT    (F_POS | F_RATIO | F_COLOR)

typedef struct s_parsed_obj
{
    t_obj_type  type;
    t_vec3      pos;
    t_vec3      dir;
    double      radius;
    double      height;
    double      ratio;
    t_vec3      color;
    double      fov;
} t_parsed_obj;

typedef struct s_material
{
    t_vec3 color;
} t_material;

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
} t_obj;

typedef struct s_camera
{
    t_vec3  pos;
    t_vec3  dir;
    double  fov;
    
    // rendering variables
    double  aspect_ratio;
    int     image_width;
    int     image_height;
    double  focal_length;
    double  viewport_height;
    double  viewport_width;
    t_vec3  camera_center;
    t_vec3  viewport_u;
    t_vec3  viewport_v;
    t_vec3  pixel_delta_u;
    t_vec3  pixel_delta_v;
    t_vec3  viewport_upper_left;
    t_vec3  pixel00_loc;
} t_camera;

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
} t_world;

#endif //MINIRT_OBJ_H
