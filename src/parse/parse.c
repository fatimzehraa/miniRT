#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include "shape.h"
#include "parse.h"
#include "minirt.h"
#include "get_next_line.h"
#include "vector.h"

static int	parse_shape(t_ctx *ctx, char *line)
{
	t_shape	*shape;

	shape = lst_new();
	if (shape == NULL)
		return (0);
	if (is_same(&line, "sp "))
	{
		if (!parse_sphere(&line, shape))
			return (free_shapes(shape), -1);
	}
	else if (is_same(&line, "cy "))
	{
		if (!parse_cy(&line, shape))
			return (free_shapes(shape), -1);
	}
	else if (is_same(&line, "pl "))
	{
		if(!parse_plane(&line, shape))
			return (free_shapes(shape), -1);
	}
	else
		return (free_shapes(shape), -1);
	if (skip(&line) && *line != '\0')
		return (free_shapes(shape), -3);
	add_back(&ctx->s, shape);
	return (1);
}

static int	parse_camera(t_ctx *ctx, char *line)
{
	t_vec	random;

	random = norm((t_vec){1, 0, 0});
	if (!is_same(&line, "C "))
		return (-1);
	skip(&line);
	if (ctx->cam)
		return -2;
	ctx->cam = malloc(sizeof(t_camera));
	if (ctx->cam == NULL)
		return (0);
	if (!parse_vec(&line, &ctx->cam->o) || !skip(&line))
		return (0);
	if (!parse_vec(&line, &ctx->cam->forward) || !skip(&line))
		return (0);
	if (!parse_float_d(&line, &ctx->cam->angle,0, 180))
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

static int	parse_light(t_ctx *ctx, char *line)
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

static int parse_ambient(t_ctx *ctx, char *line)
{
	if (!is_same(&line, "A "))
		return (-1);
	skip(&line);
	if (ctx->ambient)
		return (-2);
	ctx->ambient = malloc(sizeof(t_light));
	if (ctx->ambient == NULL)
		return (0);
	if (!parse_float_d(&line, &ctx->ambient->ratio, 0, 1) || !skip(&line))
		return (0);
	if (!parse_color(&line, &ctx->ambient->color))
		return (0);
	if (skip(&line) && *line != '\0')
		return (-3);
	return (1);
}

/* Enum ?
* if res == 1   => ok
* if res == 0   => allocation failed
* if res == -1  => type didn't match
* if res == -2  => duplicated
* **/

int match(t_ctx *ctx, char *line)
{
	int res;

	if (line[0] == '\0' || line[0] == '#')
		return 1;
	res = parse_shape(ctx, line);
	if (res != -1)
		return res;
	res = parse_camera(ctx, line);
	if (res != -1)
		return res;
	res = parse_light(ctx, line);
	if (res != -1)
		return res;
	res = parse_ambient(ctx, line);
	return res;
}

void reset_ctx(t_ctx *ctx)
{
	ctx->ambient = NULL;
	ctx->cam = NULL;
	ctx->lights = NULL;
	ctx->s = NULL;
}

int	parse(char *filename, t_ctx *ctx)
{
	int		fd;
	char	*line;
	int		res;

	reset_ctx(ctx);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		line[ft_strlen(line) - 1] = '\0';
		res = match(ctx, line);
		if (!print_err(res, fd, line))
			return (free(line), free_ctx(ctx), 0);
		free(line);
	}
	return (close(fd), 1);
}
