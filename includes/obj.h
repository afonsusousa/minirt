//
// Created by afonsusousa on 11/12/25.
//

#ifndef MINIRT_OBJ_H
#define MINIRT_OBJ_H
#include "ray.h"
#include "vec3.h"
#include "stdbool.h"
#include "stddef.h"

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

typedef struct s_obj
{
    t_obj_type  type;
    t_vec3      pos;
    t_vec3      dir;
    double      radius;
    double      height;
    double      ratio;
    t_vec3      color;
    double      fov;
} t_obj;

typedef struct s_world
{
    t_obj   *map;
    size_t  size;
} t_world;

#endif //MINIRT_OBJ_H#include "stdbool.h"
