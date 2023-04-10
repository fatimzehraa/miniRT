/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:43:26 by fael-bou          #+#    #+#             */
/*   Updated: 2023/04/10 19:42:19 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"
#include "shape.h"
#include <mlx.h>
#include "camera.h"
#include <math.h>
#include "parse.h"
#include <stdio.h>

#define ERR_MSG "please add missing elements"
#define ERR_MSG1 "(camera and ambient light are required)"


int is_rt_file(char *file)
{
	int i;

	i = 0;
	while (file[i])
		i++;
	if (i < 4)
		return (0);
	if (file[i - 1] == 't' && file[i - 2] == 'r' && file[i - 3] == '.')
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_ctx	ctx;

	if (ac != 2 || !is_rt_file(av[1]))
		return (printf("invalid arg\n"), EXIT_FAILURE);
	ctx.s = NULL;
	ctx.lights = NULL;
	ctx.cam = NULL;
	ctx.win = NULL;
	ctx.mlx = NULL;
	if (!parse(av[1], &ctx))
		return (EXIT_FAILURE);
	if (!ctx.cam || !ctx.amb)
	{
		printf(ERR_MSG ERR_MSG1);
		return (free_ctx(&ctx), EXIT_FAILURE);
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
