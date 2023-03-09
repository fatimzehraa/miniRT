#include "minirt.h"
#include "camera.h"
#include "vector.h"
#include <stdio.h>

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
	ray.dir = sub(p, cam.o);
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
	p.z = 0;
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

int intersect(t_ray r)
{
	(void)r;
	return (1);
}

void send_ray(t_camera cam, int x, int y, void *mlx, void *win)
{
	t_point p;
	p = pixel_to_point(cam, x, y);
	t_ray r;
	r = ray(cam, p);
	if (intersect(r))
		mlx_pixel_put(mlx, win, x, y, rgb(ft_map(r.dir.x, -cam.h, cam.h, 0, 1)*255, 0, ft_map(r.dir.y, -cam.h, cam.h, 0, 1) * 255));
	else
		mlx_pixel_put(mlx, win, x, y, 0xFFFFFF);
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

