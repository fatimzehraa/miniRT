#include "minirt.h"
#include "camera.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

t_camera	camera(t_point origin, t_vec forward, double fov, t_vec random)
{
	t_camera	cam;

	cam.o = origin;
	cam.forward = norm(forward);
	cam.up = cross(cam.forward, random);
	cam.right = cross(cam.up, cam.forward);
	cam.angle = fov;
	cam.h = tan(fov / 2);
	cam.w = cam.h * WIN_SIDE / WIN_SIDE;
	return (cam);
}

t_ray	ray(t_point o, t_point p)
{
	t_ray	ray;

	ray.o = o;
	ray.dir = (sub(p, o));
	ray.dir = norm(ray.dir);
	return (ray);
}

double	ft_map(double x, double from2, double to2)
{
	double	from1;
	double	to1;

	from1 = 0;
	to1 = WIN_SIDE;
	return ((x - from1) * (to2 - from2) / (to1 - from1) + from2);
}

/* t_point	pixel_to_point(t_camera cam, int x, int y)
{
	t_point	p;

	p.x = ft_map(x, 0, WIN_SIDE, -cam.w, cam.w);
	p.y = ft_map(y, 0, WIN_SIDE, cam.h, -cam.h);
	p.z = -1;
	return (p);
} 

t_pixel	point_to_pixel(t_camera cam, t_point p)
{
	int x;
	int y;

	x = ft_map(p.x, -cam.w, cam.w, 0, WIN_SIDE);
	y = ft_map(p.y, -cam.h, cam.h, 0, WIN_SIDE);
	return ((t_pixel){x, y});
}never been called */

t_equation	intersection(t_ray r, t_sphere s)
{
	t_equation	eq;
	t_point		c;

	c = sub(r.o, s.o);
	eq.a = dot(r.dir, r.dir);
	eq.b = 2 * dot(r.dir, c);
	eq.c = dot(c, c) - pow(s.r, 2);
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
	return (eq);
}
