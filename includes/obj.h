//
// Created by afonsusousa on 11/12/25.
//

#ifndef MINIRT_OBJ_H
#define MINIRT_OBJ_H
#include "vec3.h"

typedef enum
{
    OBJ_SPHERE = 1
} t_obj_type;

typedef struct s_obj
{
    t_obj_type  type;
    t_vec3      pos;
} t_obj;
#endif //MINIRT_OBJ_H