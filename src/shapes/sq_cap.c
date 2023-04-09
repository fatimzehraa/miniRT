/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sq_cap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 17:31:31 by fael-bou          #+#    #+#             */
/*   Updated: 2023/04/09 22:32:21 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "shape.h"
#include "vector.h"
#include <math.h>
#include <stdio.h>

t_equation no_intersection(t_ray r, t_shape *s)
{
	t_equation	e;

	(void) r;
	(void) s;
	e.delta = -1;
	return (e);
}

t_equation	sq_intersection(t_ray r, t_shape *s)
{
	t_equation	e;
	double		t;
	double		r1;
	double		r2;
	double		r3;

	e.shape = s;
	r1 = dot(r.o, s->forward);
	r2 = dot(r.dir, s->forward);
	r3 = dot(s->origin, s->forward);
	if (fabs(r2) > 0.001)
	{
		t = (-r1 + r3) / r2;
		if (t >= 0.001)
		{
			if (magnitude(sub(get_point(r, t), s->origin)) > s->r)
				return (e);
			e.delta = -1;
			e.t = t;
			return (e);
		}
		e.delta = -1;
		return (e);
	}
	e.delta = -1;
	return (e);
}

t_equation	cap_intersection(t_ray r, t_shape *s);

t_shape	*new_sq_cap(t_vec v)
{
	t_shape	*s;

	s = lst_new();
	if (!s)
		return (NULL);
	s->forward = v;
	s->intersection = cap_intersection;
	s->normal_at = pl_normal_at;
	return (s);
}

t_shape	*new_cub_cap(t_vec f, t_shape *s, int dir)
{
	t_shape	*cap;

	cap = new_sq_cap(f);
	if (!cap)
		return (NULL);
	cap->forward = muln(f, dir);
	cap->origin = add(s->origin, muln(cap->forward, s->r));
	cap->r = s->r;
	cap->color = s->color;
	return (cap);
}

t_vec	get_random_forward(t_vec v)
{
	t_vec	f;
	t_vec	r;

	r = vec(0, 1, 0);
	if (cmp(v, r))
		r = vec(0, 0, 1);
	f = cross(v, r);
	return (norm(f));
}

void	first_sqcap(t_shape *shape, t_shape *def)
{
	shape->forward = norm(shape->forward);
	*def = *shape;
	shape->origin = add(def->origin, muln(def->forward, def->r * -1));
	shape->forward = def->forward;
	shape->r = def->r;
}
