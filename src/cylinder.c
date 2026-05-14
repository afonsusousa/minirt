#include "obj.h"
#include "interval.h"
#include "intersection.h"
#include "vec3.h"

static void hit_cap(t_hit_ctx *ctx, t_obj *cylinder, bool bot_cap, bool *hit_anything)
{
    t_vec3 center;
    t_vec3 normal;
    t_hit temp_rec;
    t_hit_ctx temp_ctx;

    if (bot_cap)
        normal = v3_neg(cylinder->shape.cylinder.dir);
    else
        normal = cylinder->shape.cylinder.dir;

    center = v3_add(cylinder->shape.cylinder.pos, v3_muls(normal, cylinder->shape.cylinder.height / 2.0));

    temp_ctx.ray = ctx->ray;
    temp_ctx.ray_t = ctx->ray_t;
    temp_ctx.record = &temp_rec;

    if (!hit_plane_math(&temp_ctx, center, normal))
        return;
    if (v3_len_sq(v3_sub(temp_rec.p, center)) <= cylinder->shape.cylinder.radius * cylinder->shape.cylinder.radius)
    {
        *hit_anything = true;
        ctx->ray_t.max = temp_rec.t;
        *(ctx->record) = temp_rec;
    }
}

static void setup_quad(t_obj *cylinder, t_hit_ctx *ctx, t_quad_calc *calc)
{
    double axis_dot_dir;
    double axis_dot_oc;

    axis_dot_dir = v3_dot(&ctx->ray->direction, &cylinder->shape.cylinder.dir);
    axis_dot_oc = v3_dot(&calc->oc, &cylinder->shape.cylinder.dir);
    calc->a = v3_dot(&ctx->ray->direction, &ctx->ray->direction) - axis_dot_dir * axis_dot_dir;
    calc->half_b = v3_dot(&ctx->ray->direction, &calc->oc) - (axis_dot_dir * axis_dot_oc);
    calc->c = v3_dot(&calc->oc, &calc->oc) - axis_dot_oc * axis_dot_oc - cylinder->shape.cylinder.radius * cylinder->shape.cylinder.radius;
}

static bool hit_tube(t_obj *cylinder, t_hit_ctx *ctx, t_quad_calc *calc, double sqrt_d)
{
    double root;
    double proj;
    t_vec3 p_minus_c;

    root = (-calc->half_b - sqrt_d) / calc->a;
    if (surrounds(ctx->ray_t, root))
    {
        ctx->record->t = root;
        ctx->record->p = ray_at(ctx->ray, root);
        p_minus_c = v3_sub(ctx->record->p, cylinder->shape.cylinder.pos);
        proj = v3_dot(&p_minus_c, &cylinder->shape.cylinder.dir);
        if (fabs(proj) <= cylinder->shape.cylinder.height / 2.0)
            return (true);
    }
    root = (-calc->half_b + sqrt_d) / calc->a;
    if (surrounds(ctx->ray_t, root))
    {
        ctx->record->t = root;
        ctx->record->p = ray_at(ctx->ray, root);
        p_minus_c = v3_sub(ctx->record->p, cylinder->shape.cylinder.pos);
        proj = v3_dot(&p_minus_c, &cylinder->shape.cylinder.dir);
        if (fabs(proj) <= cylinder->shape.cylinder.height / 2.0)
            return (true);
    }
    return (false);
}

bool hit_cylinder(t_obj *cylinder, t_hit_ctx *ctx)
{
    t_quad_calc calc;
    double      sqrt_d;
    t_vec3      p_minus_c;
    double      proj;
    bool        hit_anything;

    hit_anything = false;
    calc.oc = v3_sub(ctx->ray->origin, cylinder->shape.cylinder.pos);
    setup_quad(cylinder, ctx, &calc);
    calc.d = calc.half_b * calc.half_b - calc.a * calc.c;
    if (calc.d >= 0)
    {
        sqrt_d = sqrt(calc.d);
        if (hit_tube(cylinder, ctx, &calc, sqrt_d))
        {
            hit_anything = true;
            ctx->ray_t.max = ctx->record->t;
            p_minus_c = v3_sub(ctx->record->p, cylinder->shape.cylinder.pos);
            proj = v3_dot(&p_minus_c, &cylinder->shape.cylinder.dir);
            set_face_normal(ctx->record, ctx->ray, v3_unit(v3_sub(p_minus_c, v3_muls(cylinder->shape.cylinder.dir, proj))));
        }
    }
    hit_cap(ctx, cylinder, false, &hit_anything);
    hit_cap(ctx, cylinder, true, &hit_anything);
    return (hit_anything);
}
