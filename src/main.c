#include "minirt.h"
#include "vector.h"
#include "shape.h"
#include <mlx.h>
#include "camera.h"
#include <math.h>
#include "parse.h"
#include <stdio.h>


int	main(int ac, char **av)
{
	t_ctx	ctx;

	if (ac != 2)
		return (EXIT_FAILURE);
	ctx.s = NULL;
	ctx.lights = NULL;
	ctx.cam = NULL;
	if (!parse(av[1], &ctx))
		return (EXIT_FAILURE);
	if (!ctx.cam || !ctx.ambient)
	{
		printf("please add missing elements (camera and ambient light are required)");
		return EXIT_FAILURE;
	}
	print_ctx(ctx);
	ctx.mlx = mlx_init();
	ctx.win = mlx_new_window(ctx.mlx, WIN_SIDE, WIN_SIDE, "minirt");
	render_(ctx);
	mlx_key_hook(ctx.win, key_hook, &ctx);
	mlx_hook(ctx.win, 17, 0, quit, &ctx);
	mlx_loop(ctx.mlx);
	return (EXIT_SUCCESS);
}
