#include "obj.h"
#include "interval.h"
#include "intersection.h"
#include "vec3.h"

static void check_cap(t_hit_ctx *ctx, t_obj *cylinder, bool bot_cap, bool *hit_anything)
{
    t_vec3      center;
    t_vec3      normal;
    t_hit       temp_rec;
    t_hit_ctx   temp_ctx;

    if (bot_cap)
        normal = v3_neg(cylinder->shape.cylinder.dir);
    else
        normal = cylinder->shape.cylinder.dir;
    
    center = v3_add(cylinder->shape.cylinder.pos, v3_muls(normal, cylinder->shape.cylinder.height / 2.0));
    
    temp_ctx.ray = ctx->ray;
    temp_ctx.ray_t = ctx->ray_t;
    temp_ctx.record = &temp_rec;

    if (!hit_plane_math(&temp_ctx, center, normal))
        return ;
    if (v3_len_sq(v3_sub(temp_rec.p, center)) <= cylinder->shape.cylinder.radius * cylinder->shape.cylinder.radius)
    {
        *hit_anything = true;
        ctx->ray_t.max = temp_rec.t;
        *(ctx->record) = temp_rec;
    }
}

static bool hit_cylinder_tube(t_obj *cylinder, t_hit_ctx *ctx)
{
    t_quad_calc calc;
    double  proj;
    t_vec3  out_normal;

    calc.oc = v3_sub(ctx->ray->origin, cylinder->shape.cylinder.pos);
    
    calc.a = v3_dot(&ctx->ray->direction, &ctx->ray->direction) - pow(v3_dot(&ctx->ray->direction, &cylinder->shape.cylinder.dir), 2);
    calc.half_b = v3_dot(&ctx->ray->direction, &calc.oc) - (v3_dot(&ctx->ray->direction, &cylinder->shape.cylinder.dir) * v3_dot(&calc.oc, &cylinder->shape.cylinder.dir));
    calc.c = v3_dot(&calc.oc, &calc.oc) - pow(v3_dot(&calc.oc, &cylinder->shape.cylinder.dir), 2) - pow(cylinder->shape.cylinder.radius, 2);
    
    calc.d = calc.half_b * calc.half_b - calc.a * calc.c;
    if (calc.d < 0)
        return (false);
        
    calc.root = (-calc.half_b - sqrt(calc.d)) / calc.a;
    if (!surrounds(ctx->ray_t, calc.root))
    {
        calc.root = (-calc.half_b + sqrt(calc.d)) / calc.a;
        if (!surrounds(ctx->ray_t, calc.root))
            return (false);
    }
    
    ctx->record->t = calc.root;
    ctx->record->p = ray_at(ctx->ray, ctx->record->t);
    t_vec3 p_minus_c = v3_sub(ctx->record->p, cylinder->shape.cylinder.pos);
    proj = v3_dot(&p_minus_c, &cylinder->shape.cylinder.dir);
    
    if (fabs(proj) > cylinder->shape.cylinder.height / 2.0)
    {
        calc.root = (-calc.half_b + sqrt(calc.d)) / calc.a;
        if (!surrounds(ctx->ray_t, calc.root))
            return (false);
        ctx->record->t = calc.root;
        ctx->record->p = ray_at(ctx->ray, ctx->record->t);
        p_minus_c = v3_sub(ctx->record->p, cylinder->shape.cylinder.pos);
        proj = v3_dot(&p_minus_c, &cylinder->shape.cylinder.dir);
        if (fabs(proj) > cylinder->shape.cylinder.height / 2.0)
            return (false);
    }
    out_normal = v3_unit(v3_sub(p_minus_c, v3_muls(cylinder->shape.cylinder.dir, proj)));
    set_face_normal(ctx->record, ctx->ray, out_normal);
    
    return (true);
}

bool hit_cylinder(t_obj *cylinder, t_hit_ctx *ctx)
{
    bool        hit_anything;

    hit_anything = false;

    if (hit_cylinder_tube(cylinder, ctx))
    {
        hit_anything = true;
        ctx->ray_t.max = ctx->record->t;
    }

    check_cap(ctx, cylinder, false, &hit_anything);
    check_cap(ctx, cylinder, true, &hit_anything);

    return (hit_anything);
}
