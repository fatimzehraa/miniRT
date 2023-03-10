#include "shape.h"
#include "stdio.h"
t_equation intersection_(t_ray r, t_shape *s)
{
	t_equation eq;
	r.o.z = -2;
	t_vec c = sub(r.o, s->origin);
 	//printf("c.x = %f, c.y = %f, c.z = %f\n", s->origin.x, s.origin.y, s.origin.z);
	eq.a = vec_dot(r.dir, r.dir);
	eq.b = 2 * vec_dot(r.dir, c);
	eq.c = vec_dot(c, c) - pow(s->r, 2);
	eq.delta = powf(eq.b, 2) - 4 * eq.a * eq.c;
	if (eq.delta < 0)
		return (eq);
	eq.t1 = (-eq.b + sqrt(eq.delta)) / (2 * eq.a);
	eq.t2 = (-eq.b - sqrt(eq.delta)) / (2 * eq.a);
	if (eq.t1 < 0 && eq.t2 < 0)
		return (eq);
	if (eq.t1 < eq.t2)
		eq.t = eq.t1;
	else
		eq.t = eq.t2;
	eq.shape = s;
	return (eq);
}

// not used yet
t_vec normal_at(t_point p, t_sphere s)
{
	(void)(p);
	(void)(s);
	t_vec n;
	n = (t_vec) {0, 0, 0};
	return (n);
}

t_shape *new_sphere(t_point origin, double r)
{
	t_shape *s;

	s = lst_new();
	s->origin = origin;
	s->r = r;
	s->intersection = intersection_;
	s->normal_at = normal_at;

	return s;
}
