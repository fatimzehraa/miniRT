#include "minirt.h"
#include "vector.h"
#include "shape.h"
#include <mlx.h>
#include "camera.h"
#include <math.h>

#include <stdio.h>
int main()
{
	void *win;
	void *mlx;
	t_shape *s;
	t_camera cam;
	t_shape *s2;

	mlx = mlx_init();
	win = mlx_new_window(mlx, WIN_SIDE, WIN_SIDE, "minirt");

	cam = camera((t_point){0,0,-1}, (t_vec){0,0,1}, M_PI/2);
	s = new_cylinder((t_point){-0.1, -0.1, 8}, (t_vec){0,1,0},1, 1);
	s2 = new_sphere((t_point){0, 0, 3}, 0.4);
	add_back(&s, s2); 
//	s->color = (t_vec){.5,0,0};
//	s2->color = (t_vec){0,0,.5};
	render_(mlx, win, s, cam);
	mlx_loop(mlx);
	
	return EXIT_SUCCESS;
}
