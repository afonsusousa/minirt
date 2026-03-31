//
// Created by afonsusousa on 11/12/25.
//

#include <stdlib.h>

#include "../includes/obj.h"
#include "../includes/vec3.h"

void    init_sphere(t_obj *sphere)
{

}

t_obj   *init_object(t_vec3 pos, t_obj_type type)
{
    t_obj *object;

    object = calloc(1, sizeof(t_obj));
    if (!object)
        return (NULL);
    object->type = type;
    if (type == OBJ_SPHERE)
        init_sphere(object);
    return (object);
}