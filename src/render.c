#include "camera.h"
#include "light.h"
#include "shape.h"
#include "minirt.h"
#include "vector.h"
#include<mlx.h>
#include<stdio.h>
#include <math.h>

//<<<<<<< Updated upstream
t_vec	calc_diff(t_ray *lray, t_light *light, t_ray *ray, t_vec normal)
{
	double	dott;
	t_vec	reflectv;
	t_vec	specular;
	t_vec	eyev;

	eyev = muln(ray->dir, -1);
	reflectv = reflect(muln(lray->dir, -1), normal);
	dott = dot(reflectv, eyev);
	specular = vec(0,0,0);
	if (dott > 0.0)
		specular = muln(muln(light->color, powf(dott, 180)), light->ratio);
	return (specular);
}



t_vec multi_lights(t_light *lights, t_equation e_min, t_ctx ctx, t_ray *r)
{
	t_light	*cur;
	t_vec	color;
	double	co;

	cur = lights;
	color = muln(mul(e_min.shape->color, ctx.ambient->color), ctx.ambient->ratio);
	while (cur)
	{
		e_min.r_light = ray(e_min.p_shape, cur->o);
		co = magnitude(sub(cur->o, e_min.p_shape));
		if (!intersect_light(e_min.r_light, ctx.s, co))
		{
			cur = cur->next;
			continue;
		} 
		co = dot(e_min.r_light.dir, e_min.shape->normal_at(e_min.p_shape, e_min.shape));
		if (co >= 0)
		{
			color = add(color, mul(muln(e_min.shape->color, co), cur->color));
			color = add(color, calc_diff(&e_min.r_light, cur, r, e_min.shape->normal_at(e_min.p_shape, e_min.shape)));
		}
		cur = cur->next;
	}
	return color;
/* =======
t_vec multi_lights(t_light *lights)
{
	t_light	*cur;

	cur = lights;
	while (cur)
	{
		
		cur = cur->next;
	}
	if (!intersect_light(e_min.r_light, ctx.s))
		return muln(e_min.shape->color, 0.1);
>>>>>>> Stashed changes */
}

t_vec	put_color(t_ray r, t_ctx ctx)
{
	t_equation	e;
	t_equation	e_min;
	t_shape		*s;
/* <<<<<<< Updated upstream
=======
	//double		co;
>>>>>>> Stashed changes */

	s = ctx.s;
	e_min.t = INFINITY;
	e_min.shape = NULL;
	while (s)
	{
		e = s->intersection(r, s);
		if (e.delta >= 0)
		{
			e.p_shape = add(muln(r.dir, e.t), r.o);
//			e.r_light = ray(e.p_shape, ctx.lights->o);
			if (e.t > 0 && e_min.t >= e.t)
				e_min = e;
		}
		s = s->next;
	}
	if (e_min.t == INFINITY)
		return (vec(0, 0, 0));
//<<<<<<< Updated upstream
	return multi_lights(ctx.lights, e_min, ctx, &r);
//=======
	/* co = dot(e_min.r_light.dir, e_min.shape->normal_at(e.p_shape, e_min.shape));
	if (co < 0)
		co = 1; */
		//return (vec(1, 1, 0));
		//return (muln(e_min.shape->color, 0.1));
		
/* 	return (mul(muln(e_min.shape->color, co), ctx.lights->color)); */
	return e_min.shape->color;
//>>>>>>> Stashed changes
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	render_(t_ctx ctx)
{
	t_ray	r;
	t_vec	clr;
	t_data	data;

	data.img = mlx_new_image(ctx.mlx, WIN_SIDE, WIN_SIDE);
	data.addr = mlx_get_data_addr(data.img,
			&data.bits_per_pixel, &data.line_length, &data.endian);
	ctx.y = 0;
	while (ctx.y < WIN_SIDE)
	{
		ctx.x = 0;
		while (ctx.x < WIN_SIDE)
		{
			ctx.p.x = ft_map(ctx.x, -ctx.cam->w, ctx.cam->w);
			ctx.p.y = ft_map(ctx.y, ctx.cam->h, -ctx.cam->h);
			r.o = ctx.cam->o;
			r.dir = norm(add(ctx.cam->forward, add(muln(ctx.cam->up, ctx.p.y),
							muln(ctx.cam->right, ctx.p.x))));
			clr = put_color(r, ctx);
			if (ctx.x == 0 && ctx.y == 0)
				print_vec(&r.dir);
			my_mlx_pixel_put(&data, ctx.x, ctx.y, rgb(clr.x, clr.y, clr.z));
			ctx.x++;
		}
		ctx.y++;
	}
	mlx_put_image_to_window(ctx.mlx, ctx.win, data.img, 0, 0);
}
