/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 20:55:34 by fael-bou          #+#    #+#             */
/*   Updated: 2023/04/10 20:19:15 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "light.h"
#include "shape.h"
#include "minirt.h"
#include "vector.h"
#include<mlx.h>
#include<stdio.h>
#include <math.h>

t_vec	calc_diff(t_ray *lray, t_light *light, t_ray *ray, t_vec normal)
{
	double	dott;
	t_vec	reflectv;
	t_vec	specular;
	t_vec	eyev;

	eyev = muln(ray->dir, -1);
	reflectv = reflect(muln(lray->dir, -1), normal);
	dott = dot(reflectv, eyev);
	specular = vec(0, 0, 0);
	if (dott > 0.0)
		specular = muln(muln(light->color, powf(dott, 180)), light->ratio);
	return (specular);
}

t_vec	multi_lights(t_light *lights, t_equation e_min, t_ctx ctx, t_ray *r)
{
	t_light	*cur;
	t_vec	color;
	double	co;

	cur = lights;
	color = muln(mul(e_min.shape->color, ctx.amb->color), ctx.amb->ratio);
	while (cur)
	{
		e_min.r_light = ray(e_min.p_shape, cur->o);
		co = magnitude(sub(cur->o, e_min.p_shape));
		if (!intersect_light(e_min.r_light, ctx.s, co))
		{
			cur = cur->next;
			continue ;
		}
		co = dot(e_min.r_light.dir, e_min.normal);
		if (co >= 0)
		{
			color = add(color, muln(mul(muln(e_min.shape->color,
								co), cur->color), cur->ratio));
			color = add(color, calc_diff(&e_min.r_light, cur, r, e_min.normal));
		}
		cur = cur->next;
	}
	return (color);
}

t_vec	put_color(t_ray r, t_ctx ctx)
{
	t_equation	e;
	t_equation	e_min;
	t_shape		*s;

	s = ctx.s;
	e_min.t = INFINITY;
	e_min.shape = NULL;
	while (s)
	{
		e = s->intersection(r, s);
		if (e.delta >= 0)
		{
			e.p_shape = add(muln(r.dir, e.t), r.o);
			e.normal = s->normal_at(e.p_shape, s);
			if (dot(e.normal, r.dir) > 0)
				e.normal = muln(e.normal, -1);
			if (e.t >= -EPSILON && e_min.t >= e.t)
				e_min = e;
		}
		s = s->next;
	}
	if (e_min.t == INFINITY)
		return (vec(0, 0, 0));
	return (multi_lights(ctx.lights, e_min, ctx, &r));
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
			my_mlx_pixel_put(&data, ctx.x, ctx.y, rgb(clr.x, clr.y, clr.z));
			ctx.x++;
		}
		ctx.y++;
	}
	mlx_put_image_to_window(ctx.mlx, ctx.win, data.img, 0, 0);
}
