#include "vec3.h"
#include "intersection.h"
#include "obj.h"
#include "ray.h"
#include "stdbool.h"

bool    hit(t_obj *obj, t_ray *ray, t_hit *record)
{
    if (obj->type == OBJ_SPHERE)
        return (hit_sphere(obj, ray, record));
}
