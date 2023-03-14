#include "minirt.h"
#include "shape.h"
#include "vector.h"

int belong_to_cylinder(t_point p, t_shape *s)
{
	double m;
	t_point A;

	m = vec_dot(vec_sub(p, s->origin), s->forward) / vec_dot(s->forward, s->forward);
	A = vec_add(s->origin, vec_muln(s->forward, m));
	if (magnitude(vec_sub(A, s->origin)) > s->height / 2)
		return (0);
	return (1);
}

t_equation cylinder_intersection(t_ray r, t_shape *s)
{
	t_equation e;
	t_vec X;

	e.shape = s;
	X = vec_sub(r.o, s->origin);
	e.a = vec_dot(r.dir, r.dir) - pow(vec_dot(r.dir, s->forward), 2);
	e.b = 2 * (vec_dot(r.dir, X) - vec_dot(r.dir, s->forward) * vec_dot(X, s->forward));
	e.c = vec_dot(X, X) - pow(vec_dot(X, s->forward), 2) - pow(s->r, 2);
	e.delta = pow(e.b, 2) - 4 * e.a * e.c;
	if (e.delta < 0)
		return (e);
	e.t1 = (-e.b - sqrt(e.delta)) / (2 * e.a);
	e.t2 = (-e.b + sqrt(e.delta)) / (2 * e.a);
	if (e.t1 < e.t2)
		e.t = e.t1;
	else
		e.t = e.t2;
	if (belong_to_cylinder(get_point(r, e.t), s) == 0)
		e.delta = -1;
	return (e);
}

t_shape *new_cylinder(t_point p, t_vec v, double r, double h)
{
	t_shape *s;

	s = lst_new();
	s->origin = p;
	s->forward = v;
	s->r = r;
	s->height = h;
	s->intersection = cylinder_intersection;
	return (s);
}
