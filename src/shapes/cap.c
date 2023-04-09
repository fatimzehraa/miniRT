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
	if (fabs(r2) > 0.001)
	{
		t = (-r1 + r3) / r2;
		if (t >= 0.001)
		{
			t_point p = get_point(r, t);
			if (magnitude(sub(p, s->origin)) > s->r)
			{
				e.t = t;
				e.delta = -1;
				return (e);
			}
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

t_shape	*new_cap(t_shape *cy, int dir)
{
	t_shape	*s;
	t_point p;

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
