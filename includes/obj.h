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
