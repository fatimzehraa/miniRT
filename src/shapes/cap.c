/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 20:37:33 by fael-bou          #+#    #+#             */
/*   Updated: 2023/04/09 23:51:20 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "shape.h"
#include "vector.h"
#include <math.h>
#include <stdio.h>

t_equation	cap_intersection(t_ray r, t_shape *s)
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
	e.delta = -1;
	if (fabs(r2) > 0.001)
	{
		t = (-r1 + r3) / r2;
		if (t >= 0.001)
		{
			if (magnitude(sub(get_point(r, t), s->origin)) > s->r)
				return (e);
			e.delta = 1;
			e.t = t;
			e.t1 = t;
			e.t2 = t;
			return (e);
		}
	}
	return (e);
}

t_shape	*new_cap(t_shape *cy, int dir)
{
	t_shape	*s;
	t_point	p;

	s = lst_new();
	s->forward = muln(cy->forward, dir);
	p = add(cy->origin, muln(s->forward, cy->height / 2));
	s->origin = p;
	s->r = cy->r;
	s->color = cy->color;
	s->intersection = cap_intersection;
	s->normal_at = pl_normal_at;
	return (s);
}
