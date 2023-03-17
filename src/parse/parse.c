#include <fcntl.h>
#include <unistd.h>
#include "shape.h"
#include "parse.h"
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


static t_shape *parse_shape(char *line)
{
	t_shape *shape;

	shape = lst_new();
	if (shape == NULL)
		return (NULL);
	if (is_same(&line, "sp "))
		parse_sphere(&line, shape);
	else if (is_same(&line, "cy "))
		parse_cy(&line, shape);
	else if (is_same(&line, "pl "))
		parse_plane(&line, shape);
	else
		return (free(shape), NULL);
	return (shape);
}

t_shape *parse(char *filename)
{
	int fd;
	char *line;
	t_shape *shape;

	shape = NULL;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);

	while(1){
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		line[ft_strlen(line) - 1] = 0; // remove \n
		add_back(&shape, parse_shape(line));
		free(line);
	}
	return (close(fd), shape);
}
