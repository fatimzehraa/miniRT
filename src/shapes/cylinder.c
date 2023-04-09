/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:46:56 by fael-bou          #+#    #+#             */
/*   Updated: 2023/04/09 21:46:57 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "shape.h"
#include "vector.h"

int	belong_to_cylinder(t_point p, t_shape *s)
{
	double	m;
	t_point	a;

	m = dot(sub(p, s->origin), s->forward) / dot(s->forward, s->forward);
	a = add(s->origin, muln(s->forward, m));
	if (magnitude(sub(a, s->origin)) > s->height / 2)
		return (0);
	return (1);
}

t_equation	cylinder_intersection(t_ray r, t_shape *s)
{
	t_equation	e;
	t_vec		x;

	e.shape = s;
	x = sub(r.o, s->origin);
	e.a = dot(r.dir, r.dir) - pow(dot(r.dir, s->forward), 2);
	e.b = 2 * (dot(r.dir, x) - dot(r.dir, s->forward) * dot(x, s->forward));
	e.c = dot(x, x) - pow(dot(x, s->forward), 2) - pow(s->r, 2);
	e.delta = pow(e.b, 2) - 4 * e.a * e.c;
	if (e.delta < -EPSILON)
		return (e);
	e.t1 = (-e.b - sqrt(e.delta)) / (2 * e.a);
	e.t2 = (-e.b + sqrt(e.delta)) / (2 * e.a);
	if (e.t1 < EPSILON && e.t2 < EPSILON)
	{
		e.delta = -1;
		return (e);
	}
	if (e.t1 < e.t2)
		e.t = e.t1;
	else
		e.t = e.t2;
	if (belong_to_cylinder(get_point(r, e.t), s) == 0)
		e.delta = -1;
	return (e);
}

t_vec	cy_normal_at(t_point p, t_shape *s)
{
	t_vec	n;
	t_point	a;
	double	m;

	m = dot(sub(p, s->origin), s->forward) / dot(s->forward, s->forward);
	a = add(s->origin, muln(s->forward, m));
	n = sub(p, a);
	return (norm(n));
}

t_shape	*new_cylinder(t_point p, t_vec v, double r, double h)
{
	t_shape	*s;

	s = lst_new();
	s->origin = p;
	s->forward = v;
	s->r = r;
	s->height = h;
	s->intersection = cylinder_intersection;
	s->normal_at = cy_normal_at;
	return (s);
}
