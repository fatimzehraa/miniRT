#include <fcntl.h>
#include <math.h>
#include <unistd.h>
#include "shape.h"
#include "parse.h"
#include "minirt.h"
#include "get_next_line.h"


static int parse_sphere(char **line, t_shape *shape)
{
	if (!parse_vec(line, &shape->origin) || !skip(line))
		return (0);

	if (!parse_float(line, &shape->r) || !skip(line))
		return (0);

	if (!parse_color(line, &shape->color))
		return (0);

	shape->intersection = sphere_intersection;

	return (1);
}

static int parse_cy(char **line, t_shape *shape)
{
	if (!parse_vec(line, &shape->origin) || !skip(line))
		return (0);

	if (!parse_vec(line, &shape->forward) || !skip(line))
		return (0);

	if (!parse_float(line, &shape->r) || !skip(line))
		return (0);

	if (!parse_float(line, &shape->height) || !skip(line))
		return (0);

	if (!parse_color(line, &shape->color))
		return (0);

	shape->intersection = cylinder_intersection;
	return (1);
}

static int parse_plane(char **line, t_shape *shape)
{
	if (!parse_vec(line, &shape->origin) || !skip(line))
		return (0);

	if (!parse_vec(line, &shape->forward) || !skip(line))
		return (0);

	if (!parse_color(line, &shape->color))
		return (0);

	shape->intersection = plane_intersection;
	return (1);
}


static int parse_shape(t_ctx *ctx, char *line)
{
	t_shape *shape;

	shape = lst_new();
	if (shape == NULL)
		return (0);
	if (is_same(&line, "sp "))
		parse_sphere(&line, shape);
	else if (is_same(&line, "cy "))
		parse_cy(&line, shape);
	else if (is_same(&line, "pl "))
		parse_plane(&line, shape);
	else
		return (free(shape), -1);
	add_back(&ctx->s, shape);
	return (1);
}

static int parse_camera(char *line, t_ctx *ctx)
{
	if (!is_same(&line, "C "))
		return (-1);
	ctx->cam = malloc(sizeof(t_camera));
	if (ctx->cam == NULL)
		return (0);
	if (!parse_vec(&line, &ctx->cam->o) || !skip(&line))
		return (0);
	if (!parse_vec(&line, &ctx->cam->forward) || !skip(&line))
		return (0);
	if (!parse_float(&line, &ctx->cam->angle))
		return (0);
	*ctx->cam = camera(ctx->cam->o, ctx->cam->forward, ctx->cam->angle);
	return (1);
}

static int parse_light(char *line, t_ctx *ctx)
{
	t_light *light;

	if (!is_same(&line, "L "))
		return (-1);
	light = malloc(sizeof(t_light));
	if (light == NULL)
		return (0);
	if (!parse_vec(&line, &light->o) || !skip(&line))
		return (0);
	if (!parse_float(&line, &light->ratio) || !skip(&line))
		return (0);
	if (!parse_color(&line, &light->color))
		return (0);
	ctx->lights = light;
	return (1);
}

int	parse(char *filename, t_ctx *ctx)
{
	int fd;
	char *line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);

	while(1){
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		line[ft_strlen(line) - 1] = 0; // remove \n
		if (parse_shape(ctx, line) != -1 || parse_camera(line, ctx) != -1 || parse_light(line, ctx) != -1)
			;
		free(line);
	}
	return (close(fd), 1);
}
