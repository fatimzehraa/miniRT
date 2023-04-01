#include "minirt.h"
#include "shape.h"
#include "stdio.h"
#include "vector.h"

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
	if (eq.t1 > EPSILON && eq.t1 < eq.t2)
		eq.t = eq.t1;
	else
		eq.t = eq.t2;
	return (eq);
}

t_vec	sp_normal_at(t_point p, t_shape *s)
{
	t_sphere	*sp;

	sp = (t_sphere *) s;
	return (norm(sub(p, sp->o)));
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
