#include "minirt.h"
#include "shape.h"
#include "vector.h"
#include <math.h>

#include <stdio.h>
t_equation plane_intersection(t_ray r, t_shape *s)
{
	t_equation e;
	double t;

	e.shape = s;
	double r1 = vec_dot(r.o, s->forward);
	double r2 = vec_dot(r.dir, s->forward);
	double r3 = vec_dot(s->origin, s->forward);
	if (fabs(r2) > 0.001)
	{
		t = (-r1 + r3) / r2;
		if (t >= 0.001)
		{
			e.delta = 1;
			e.t1 = t;
			return (e);
		}
		e.delta = -1;
		return (e);
	}
	e.delta = -1;
	return (e);
}

t_shape *new_plane(t_point p, t_vec v)
{
	t_shape *s;

	s = lst_new();
	s->origin = p;
	s->forward = v;
	s->intersection = plane_intersection;
	return (s);
}
