#include "minirt.h"
#include "vector.h"
#include <mlx.h>
#include "camera.h"
#include <math.h>

/* int main(void)
{
	void *win;
	void *mlx;
	 t_point center;
	t_point o;
	t_vec forward;
	t_camera cam;
	o.x = 0;
	o.y = 0;
	o.z = -1;
	forward.x = 500;
	forward.y = 500;
	forward.z = 1;

	cam = camera(o, forward, M_PI/2);
	center.x = (double)WIN_SIDE/2;
	center.y = (double)WIN_SIDE/2; 
	t_point p1;
	t_point p2;
	p1.x = 0;
	p1.y = 0;
	p2.x = 600;
	p2.y = 400;
	mlx = mlx_init();
	win = mlx_new_window(mlx, WIN_SIDE, WIN_SIDE, "minirt");
	t_sphere s;
	s.o = (t_point){0.5, 0.50, 1};
	s.r = 1;
	t_sphere s1;
	s1.o = (t_point){-1, 1, 0};
	s1.r = 0.5;
	sphere(s1, cam, mlx, win);
	sphere(s, cam, mlx, win);
	mlx_loop(mlx);

	return (0);
} */

#include "minirt.h"
#include "shape.h"

void render_(void *mlx, void *win, t_shape *s, t_camera cam)
{
	int x;
	int y;
	t_ray r;
	t_point p;
	t_equation e;

	y = 0;
	while (y < WIN_SIDE)
	{
		x = 0;
		while (x < WIN_SIDE)
		{
			p.x = ft_map(x, 0, WIN_SIDE, -cam.w, cam.w);
			p.y = ft_map(y, 0, WIN_SIDE, cam.h, -cam.h);
			r = ray(cam, p);
			e = s->intersection(r, s);
			if (e.delta > 0)
		 		mlx_pixel_put(mlx, win, x, y, rgb(ft_map(r.dir.x, cam.h, -cam.h, 0, 1)*255, 0, ft_map(r.dir.y, -cam.h, cam.h, 0, 1) * 255));
			x++;
		}
		y++;
	}
}

#include <stdio.h>
int main()
{
	void *win;
	void *mlx;
	t_shape *s;
	t_camera cam;

	mlx = mlx_init();
	win = mlx_new_window(mlx, WIN_SIDE, WIN_SIDE, "minirt");

	cam = camera((t_point){0,0,-1}, (t_vec){0,0,1}, M_PI/2);
	t_point p;
	p.x = 0;
	p.y = 0;
	p.z = 0;
	s = new_sphere(p, 0.4);
	render_(mlx, win, s, cam);
	mlx_loop(mlx);
	
	return EXIT_SUCCESS;
}
