#include "minirt.h"
#include "vector.h"
#include "shape.h"
#include <mlx.h>
#include "camera.h"
#include <math.h>

#include <stdio.h>
int main()
{
	t_ctx ctx;
	t_shape *s2;

	ctx.mlx = mlx_init();
	ctx.win = mlx_new_window(ctx.mlx, WIN_SIDE, WIN_SIDE, "minirt");
	ctx.s = NULL;

	ctx.cam = camera((t_point){0,0,-1}, (t_vec){0,0,1}, M_PI/2);
	ctx.lights = new_light((t_point){-3,0,5}, (t_vec){1,1,1});
		t_vec v = (t_vec){0,1,0};
	v = norm(v);
	t_shape *s1= new_sphere((t_point){0, 0, 5}, 1.4);
	s2 = new_cylinder((t_point){0, 0, 5}, v,1, 3);
	add_back(&ctx.s, s1); 
	//add_back(&ctx.s, s2); 
	ctx.s->color = (t_vec){.5,0,0.3};
	s2->color = (t_vec){0.80,1,.5};
	render_(ctx);
	mlx_loop(ctx.mlx);
	
	return EXIT_SUCCESS;
}
