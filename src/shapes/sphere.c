/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:46:36 by fael-bou          #+#    #+#             */
/*   Updated: 2023/04/10 20:42:44 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "shape.h"
#include "stdio.h"
#include "vector.h"

int	min_positive(double a, double b)
{
	if (a < 0 && b < 0)
		return (-1);
	if (a < 0)
		return (b);
	return (a);
}

t_equation	sphere_intersection(t_ray r, t_shape *s)
{
	t_equation	eq;
	t_point		c;

	eq.shape = s;
	c = sub(r.o, s->origin);
	eq.a = dot(r.dir, r.dir);
	eq.b = 2 * dot(r.dir, c);
	eq.c = dot(c, c) - pow(s->r, 2);
	eq.delta = powf(eq.b, 2) - 4 * eq.a * eq.c;
	if (eq.delta < -EPSILON)
		return (eq);
	eq.t1 = (-eq.b + sqrt(eq.delta)) / (2 * eq.a);
	eq.t2 = (-eq.b - sqrt(eq.delta)) / (2 * eq.a);
	if (eq.t1 < EPSILON && eq.t2 < EPSILON)
	{
		eq.delta = -1;
		return (eq);
	}
	if (fabs(eq.t1) < fabs(eq.t2))
		eq.t = fabs(eq.t1);
	else
		eq.t = fabs(eq.t2);
	return (eq);
}

t_vec	sp_normal_at(t_point p, t_shape *s)
{
	return (norm(sub(p, s->origin)));
}

t_shape	*new_sphere(t_point origin, double r)
{
	t_shape	*s;

	s = lst_new();
	s->origin = origin;
	s->r = r;
	s->intersection = sphere_intersection;
	s->normal_at = sp_normal_at;
	return (s);
}
