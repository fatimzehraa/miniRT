#include "camera.h"
#include "light.h"
#include "shape.h"
#include "minirt.h"
#include "vector.h"
#include<mlx.h>
#include<stdio.h>
#include <math.h>

t_vec put_color(t_ray r, t_ctx ctx)
{
	t_equation e;
	t_equation e_min;
	t_shape *s = ctx.s;

	e_min.t = INFINITY;
	e_min.shape = NULL;
	while (s)
	{
		e = s->intersection(r, s);
		if (e.delta >= 0)
		{
			e.p_shape = vec_add(vec_muln(r.dir, e.t), r.o);
			e.r_light = ray(ctx.lights->o, e.p_shape);
			if (e.t > 0 )//&& e_min.t >= e.t && intersect_light(e.r_light, ctx.s))
				e_min = e;
		}
		s = s->next;
	}
	if (e_min.t == INFINITY)
		return ((t_vec){0,0,0});
    double cos = -vec_dot(e_min.r_light.dir, e_min.shape->normal_at(e.p_shape, e_min.shape) );
	if (cos < 0)
		return ((t_vec){0,0,0});
	return (vec_muln(e_min.shape->color, cos));
}

void render_(t_ctx ctx)
{
	int x;
	int y;
	t_ray r;
	t_point p;
	t_vec color;

	y = 0;
	while (y < WIN_SIDE)
	{
		x = 0;
		while (x < WIN_SIDE)
		{
			p.x = ft_map(x, 0, WIN_SIDE, -ctx.cam->w, ctx.cam->w);
			p.y = ft_map(y, 0, WIN_SIDE, ctx.cam->h, -ctx.cam->h);
			p.z = 0; // Added
			r = ray(ctx.cam->o, p);
			color = put_color(r, ctx);
			mlx_pixel_put(ctx.mlx, ctx.win, x, y, rgb(color.x, color.y, color.z));
			x++;
		}
		y++;
	}
}
