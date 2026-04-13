#include "parsing.h"
#include "../../includes/obj.h"
#include "../../includes/color.h"
#include <stdint.h>
#include <stddef.h>

static bool	handle_unique_obj(t_world *wrld, t_parsed_obj *parsed)
{
	if (parsed->type == OBJ_CAMERA)
	{
		wrld->camera.pos = parsed->pos;
		wrld->camera.dir = parsed->dir;
		wrld->camera.fov = parsed->fov;
		return (true);
	}
	if (parsed->type == OBJ_AMBIENT)
	{
		wrld->ambient.ratio = parsed->ratio;
		wrld->ambient.color = parsed->color;
		return (true);
	}
	if (parsed->type == OBJ_LIGHT)
	{
		wrld->lights[wrld->num_lights].pos = parsed->pos;
		wrld->lights[wrld->num_lights].ratio = parsed->ratio;
		wrld->lights[wrld->num_lights++].color = parsed->color;
		return (true);
	}
	return (false);
}

void	pack_object(t_world *wrld, t_parsed_obj *parsed)
{
	t_obj	*new_obj;

	if (parsed->type == ERR || handle_unique_obj(wrld, parsed))
		return ;
	wrld->materials[wrld->num_materials].color = parsed->color;
	new_obj = &wrld->objects[wrld->num_objects++];
	new_obj->type = parsed->type;
	new_obj->mat_idx = wrld->num_materials++;
	if (parsed->type == OBJ_SPHERE)
	{
		new_obj->shape.sphere.center = parsed->pos;
		new_obj->shape.sphere.radius = parsed->radius;
	}
	else if (parsed->type == OBJ_PLANE)
	{
		new_obj->shape.plane.pos = parsed->pos;
		new_obj->shape.plane.dir = parsed->dir;
	}
	else if (parsed->type == OBJ_CYLINDER)
	{
		new_obj->shape.cylinder.pos = parsed->pos;
		new_obj->shape.cylinder.dir = parsed->dir;
		new_obj->shape.cylinder.radius = parsed->radius;
		new_obj->shape.cylinder.height = parsed->height;
	}
}
