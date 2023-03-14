#include "camera.h"
#include "shape.h"
#include "minirt.h"
#include "vector.h"
#include<mlx.h>
#include<stdio.h>
#include <math.h>

t_vec put_color(t_ray r, t_shape *s)
{
	t_equation e;
	t_equation e_min;

	e_min.t = INFINITY;
	while (s)
	{
		e = s->intersection(r, s);
		if (e.delta > 0)
		{
			if (e_min.t > e.t)
					e_min = e;
		}
		s = s->next;
	}
	if (e_min.t == INFINITY)
		return ((t_vec){0,0,0});
	return (e_min.shape->color);
}

void render_(void *mlx, void *win, t_shape *s, t_camera cam)
{
	int x;
	int y;
	t_ray r;
	t_point p;
	t_vec color;

	y = 0;
	while (y < WIN_SIDE)
	{
		x = 0;
		while (x < WIN_SIDE)
		{
			p.x = ft_map(x, 0, WIN_SIDE, -cam.w, cam.w);
			p.y = ft_map(y, 0, WIN_SIDE, cam.h, -cam.h);
			r = ray(cam, p);
			color = put_color(r, s);
			mlx_pixel_put(mlx, win, x, y, rgb(color.x, color.y, color.z));
			x++;
		}
		y++;
	}
}
