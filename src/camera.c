#include "minirt.h"
#include "camera.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

t_camera	camera(t_point origin, t_vec forward, double fov)
{
	t_camera	cam;
	cam.o = origin;
	cam.forward = forward;
	cam.angle = fov;
	cam.h = tan(fov / 2);
	cam.w = cam.h * WIN_SIDE / WIN_SIDE;
	return (cam);
}

t_ray	ray(t_camera cam, t_point p)
{
	t_ray	ray;
	ray.o = cam.o;
	ray.dir = (sub(p, cam.o));
	ray.dir.z = 1;
	ray.dir = norm(ray.dir);
	return (ray);
}

double ft_map(double x, double from1, double to1, double from2, double to2)
{
	return (x - from1) * (to2 - from2) / (to1 - from1) + from2;
}

t_point	pixel_to_point(t_camera cam, int x, int y)
{
	t_point	p;
	p.x = ft_map(x, 0, WIN_SIDE, -cam.w, cam.w);
	p.y = ft_map(y, 0, WIN_SIDE, cam.h, -cam.h);
	p.z = -1;
	return (p);
} 

t_pixel point_to_pixel(t_camera cam, t_point p)
{
	int x;
	int y;
	x = ft_map(p.x, -cam.w, cam.w, 0, WIN_SIDE);
	y = ft_map(p.y, -cam.h, cam.h, 0, WIN_SIDE);
	return ((t_pixel){x, y});
}

/* int intersect(double a, double b, double c, int x, int y)
{
	double delta;
	double t1;
	double t2;

	(void)(x);
	(void)(y);
	delta = pow(b, 2) - 4 * a * c;
	if (delta < 0)
		return (0);
	t1 = (-b + sqrt(delta)) / (2 * a);
	t2 = (-b - sqrt(delta)) / (2 * a);
	if (t1 < 0 && t2 < 0)
		return (0);
	if (t1 < t2
		send_ray(cam, x, y, s, mlx, win);
	return (1);
} */

int intersect(t_ray r, t_sphere s, t_camera cam, int x, int y, void *mlx, void *win)
{
	double a;
	double b;
	double c;
	double delta;
	 double t1;
	 double t2;


	/* (void)(x);
	(void)(y);
	(void)(mlx);
	(void)(win);
	(void)(cam); */
	(void)(s);
	r.o.z = -2;
	a = vec_dot(r.dir, r.dir);
	b = 2 * vec_dot(r.dir, r.o);
	//c = vec_dot(sub(r.o, s.o), sub(r.o, s.o)) - pow(s.r, 2);
	c = vec_dot(r.o, r.o) - 1;
	delta = powf(b, 2) - 4 * a * c;
	/* printf("delta = %f\n", sqrt(delta));
	exit(0); */
	if (delta < 0){
		return (0);
	}
	t1 = (-b + sqrt(delta)) / (2 * a);
	t2 = (-b - sqrt(delta)) / (2 * a);
	/* if (t1 < 0 && t2 < 0)
		return (0); */
	if (t1 < t2)
		mlx_pixel_put(mlx, win, x, y, rgb(ft_map(t1 * r.dir.x, -cam.h, cam.h, 0, 1)*255, 0, ft_map(t1 * r.dir.y, -cam.h, cam.h, 0, 1) * 255));
	else{
		mlx_pixel_put(mlx, win, x, y, rgb(ft_map(t2 * r.dir.x, -cam.h, cam.h, 0, 1)*255, 0, ft_map(t2 * r.dir.y, -cam.h, cam.h, 0, 1) * 255));
	}
	return (1);
}

int min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

/* int solution(t_ray r, t_sphere s)
{
} */

void send_ray(t_camera cam, int x, int y, void *mlx, void *win)
{
	t_point p;
	p = pixel_to_point(cam, x, y);
	t_ray r;
	r = ray(cam, p);
	if (1)
		mlx_pixel_put(mlx, win, x, y, rgb(ft_map(r.dir.x, -cam.h, cam.h, 0, 1)*255, 0, ft_map(r.dir.y, -cam.h, cam.h, 0, 1) * 255));
	else
		mlx_pixel_put(mlx, win, x, y, 0x000000);
}
#include "stdio.h"

void draw(t_camera cam, void *mlx, void *win)
{
	int x;
	int y;

	x = 0;
	while (x < WIN_SIDE)
	{
		y = 0;
		while (y < WIN_SIDE)
		{
			send_ray(cam, x, y, mlx, win);
			y++;
		}
		x++;
	}
}

