#include "parse.h"
#include "shape.h"

int	parse_sphere(char **line, t_shape *shape)
{
	if (!parse_vec(line, &shape->origin) || !skip(line))
		return (0);
	if (!parse_float(line, &shape->r) || !skip(line))
		return (0);
	if (!parse_color(line, &shape->color))
		return (0);
	shape->normal_at = sp_normal_at;
	shape->intersection = sphere_intersection;
	return (1);
}

int	parse_cy(char **line, t_shape *shape)
{
	if (!parse_vec(line, &shape->origin) || !skip(line))
		return (0);
	if (!parse_vec(line, &shape->forward) || !skip(line))
		return (0);
	shape->forward = norm(shape->forward);
	if (!parse_float(line, &shape->r) || !skip(line))
		return (0);
	if (!parse_float(line, &shape->height) || !skip(line))
		return (0);
	if (!parse_color(line, &shape->color))
		return (0);
	shape->intersection = cylinder_intersection;
	shape->normal_at = cy_normal_at;
	add_back(&shape, new_cap(shape, 1));
	add_back(&shape, new_cap(shape, -1));
	return (1);
}

int	parse_plane(char **line, t_shape *shape)
{
	if (!parse_vec(line, &shape->origin) || !skip(line))
		return (0);
	if (!parse_vec(line, &shape->forward) || !skip(line))
		return (0);
	shape->forward = norm(shape->forward);
	if (!parse_color(line, &shape->color))
		return (0);
	shape->normal_at = pl_normal_at;
	shape->intersection = plane_intersection;
	return (1);
}

int	parse_color(char **p, t_vec *color)
{
	if (!parse_int(p, &color->x))
		return (0);
	if (**p == ',')
		(*p)++;
	else
		return (0);
	if (!parse_int(p, &color->y))
		return (0);
	if (**p == ',')
		(*p)++;
	else
		return (0);
	if (!parse_int(p, &color->z))
		return (0);
	if (color->x < 0 || color->x > 255)
		return (0);
	if (color->y < 0 || color->y > 255)
		return (0);
	if (color->z < 0 || color->z > 255)
		return (0);
	color->x = color->x / 255;
	color->y = color->y / 255;
	color->z = color->z / 255;
	return (1);
}
