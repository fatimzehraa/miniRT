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
	t_ray r_light;
	t_shape *s = ctx.s;
	t_point p_shape;

	e_min.t = INFINITY;
	while (s)
	{
		e = s->intersection(r, s);
		if (e.delta > 0)
		{
			p_shape = vec_add(vec_muln(r.dir, e.t), r.o);
			r_light = ray(p_shape, ctx.lights->o);
			(void)r_light;
			if (e.t > 0 && e_min.t > e.t && intersect_light(r_light, ctx.s))
				e_min = e;
		}
		s = s->next;
	}
	if (e_min.t == INFINITY)
		return ((t_vec){0,0,0});
	return (e_min.shape->color);
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
			p.x = ft_map(x, 0, WIN_SIDE, -ctx.cam.w, ctx.cam.w);
			p.y = ft_map(y, 0, WIN_SIDE, ctx.cam.h, -ctx.cam.h);
			r = ray(ctx.cam.o, p);
			color = put_color(r, ctx);
			mlx_pixel_put(ctx.mlx, ctx.win, x, y, rgb(color.x, color.y, color.z));
			x++;
		}
		y++;
	}
}
