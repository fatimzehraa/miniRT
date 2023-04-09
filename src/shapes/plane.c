/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:46:41 by fael-bou          #+#    #+#             */
/*   Updated: 2023/04/09 21:46:43 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "shape.h"
#include "vector.h"
#include <math.h>
#include <stdio.h>

t_equation	plane_intersection(t_ray r, t_shape *s)
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
			e.delta = 1;
			e.t = t;
			return (e);
		}
		e.delta = -1;
		return (e);
	}
	e.delta = -1;
	return (e);
}

t_vec	pl_normal_at(t_point p, t_shape *s)
{
	(void)(p);
	return (norm(s->forward));
}

t_shape	*new_plane(t_point p, t_vec v)
{
	t_shape	*s;

	s = lst_new();
	s->origin = p;
	s->forward = v;
	s->intersection = plane_intersection;
	s->normal_at = pl_normal_at;
	return (s);
}
