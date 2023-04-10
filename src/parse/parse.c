/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 20:39:45 by fael-bou          #+#    #+#             */
/*   Updated: 2023/04/09 22:45:59 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include "shape.h"
#include "parse.h"
#include "minirt.h"
#include "get_next_line.h"
#include "vector.h"

int	parse_shape(t_ctx *ctx, char *line)
{
	t_shape	*shape;
	int		ret;

	shape = new_sq_cap(vec(0, 0, 0));
	if (shape == NULL)
		return (0);
	if (is_same(&line, "sp "))
		ret = parse_sphere(&line, shape);
	else if (is_same(&line, "cy "))
		ret = parse_cy(&line, shape);
	else if (is_same(&line, "pl "))
		ret = parse_plane(&line, shape);
	else if (is_same(&line, "cb "))
		ret = parse_cube(&line, shape);
	else
		return (free_shapes(shape), -1);
	if (ret == 0)
		return (free_shapes(shape), 0);
	if (skip(&line) && *line != '\0')
		return (free_shapes(shape), -3);
	return (add_back(&ctx->s, shape), 1);
}

int	parse_camera(t_ctx *ctx, char *line)
{
	t_vec	random;

	random = norm((t_vec){1, 0, 0});
	if (!is_same(&line, "C "))
		return (-1);
	skip(&line);
	if (ctx->cam)
		return (-2);
	ctx->cam = malloc(sizeof(t_camera));
	if (ctx->cam == NULL)
		return (0);
	if (!parse_vec(&line, &ctx->cam->o) || !skip(&line))
		return (0);
	if (!parse_vec(&line, &ctx->cam->forward) || !skip(&line))
		return (0);
	if (!parse_float_d(&line, &ctx->cam->angle, 0, 180))
		return (0);
	ctx->cam->angle = ctx->cam->angle * M_PI / 180;
	ctx->cam->forward = norm(ctx->cam->forward);
	if (cmp(ctx->cam->forward, random))
		random = norm((t_vec){0, 1, 0});
	*ctx->cam = camera(ctx->cam->o, ctx->cam->forward, ctx->cam->angle, random);
	if (skip(&line) && *line != '\0')
		return (-3);
	return (1);
}

int	parse_light(t_ctx *ctx, char *line)
{
	t_light	*light;

	if (!is_same(&line, "l "))
		return (-1);
	skip(&line);
	light = malloc(sizeof(t_light));
	if (light == NULL)
		return (0);
	light->next = NULL;
	if (!parse_vec(&line, &light->o) || !skip(&line))
		return (0);
	if ((!parse_float_d(&line, &light->ratio, 0, 1)) || !skip(&line))
		return (0);
	if (!parse_color(&line, &light->color))
		return (0);
	add_back_light(&ctx->lights, light);
	if (skip(&line) && *line != '\0')
		return (-3);
	return (1);
}

int	parse_ambient(t_ctx *ctx, char *line)
{
	if (!is_same(&line, "A "))
		return (-1);
	skip(&line);
	if (ctx->amb)
		return (-2);
	ctx->amb = malloc(sizeof(t_light));
	if (ctx->amb == NULL)
		return (0);
	if (!parse_float_d(&line, &ctx->amb->ratio, 0, 1) || !skip(&line))
		return (0);
	if (!parse_color(&line, &ctx->amb->color))
		return (0);
	if (skip(&line) && *line != '\0')
		return (-3);
	return (1);
}
