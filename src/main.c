#include "minirt.h"
#include "vector.h"
#include "shape.h"
#include <mlx.h>
#include "camera.h"
#include <math.h>
#include "parse.h"

#include <stdio.h>
int main(int ac, char **av)
{
	t_ctx ctx;

	if (ac != 2)
		return EXIT_FAILURE;

	ctx.s = NULL;
	ctx.lights = NULL;
	ctx.cam = NULL;

	if (!parse(av[1], &ctx))
		return EXIT_FAILURE;
	//*ctx.cam = camera((t_point){0,0,-1}, (t_vec){0,0,1}, M_PI/4);
	//ctx.lights = new_light((t_point){0,5,3}, (t_vec){1,1,1});
	// debug_ctx(ctx);
	print_ctx(ctx);

	ctx.mlx = mlx_init();
	ctx.win = mlx_new_window(ctx.mlx, WIN_SIDE, WIN_SIDE, "minirt");
	render_(ctx);
	mlx_loop(ctx.mlx);
	
	return EXIT_SUCCESS;
}
