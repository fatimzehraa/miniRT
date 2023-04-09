/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:47:24 by fael-bou          #+#    #+#             */
/*   Updated: 2023/04/09 21:58:01 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "shape.h"
#include "vector.h"

int	parse_cube(char **line, t_shape *shape)
{
	t_shape	def;
	t_vec	f;

	skip(line);
	if (!parse_vec(line, &shape->origin) || !skip(line))
		return (0);
	if (!parse_vec(line, &shape->forward) || !skip(line))
		return (0);
	if (!parse_float_d(line, &shape->r, 0, -1) || !skip(line))
		return (0);
	if (!parse_color(line, &shape->color))
		return (0);
	first_sqcap(shape, &def);
	if (!add_back(&shape, new_cub_cap(def.forward, &def, -1)))
		return (0);
	if (!add_back(&shape, new_cub_cap(def.forward, &def, 1)))
		return (0);
	f = get_random_forward(def.forward);
	if (!add_back(&shape, new_cub_cap(f, &def, 1)))
		return (0);
	if (!add_back(&shape, new_cub_cap(f, &def, -1)))
		return (0);
	f = cross(def.forward, f);
	return (add_back(&shape, new_cub_cap(f, &def, 1))
		&& add_back(&shape, new_cub_cap(f, &def, -1)));
}

int	parse_sphere(char **line, t_shape *shape)
{
	skip(line);
	if (!parse_vec(line, &shape->origin) || !skip(line))
		return (0);
	if (!parse_float_d(line, &shape->r, 0, -1) || !skip(line))
		return (0);
	if (!parse_color(line, &shape->color))
		return (0);
	shape->normal_at = sp_normal_at;
	shape->intersection = sphere_intersection;
	return (1);
}

int	parse_cy(char **line, t_shape *shape)
{
	skip(line);
	if (!parse_vec(line, &shape->origin) || !skip(line))
		return (0);
	if (!parse_vec(line, &shape->forward) || !skip(line))
		return (0);
	shape->forward = norm(shape->forward);
	if (!parse_float_d(line, &shape->r, 0, -1) || !skip(line))
		return (0);
	if (!parse_float_d(line, &shape->height, 0, -1) || !skip(line))
		return (0);
	if (!parse_color(line, &shape->color))
		return (0);
	shape->intersection = cylinder_intersection;
	shape->normal_at = cy_normal_at;
	if (!add_back(&shape, new_cap(shape, 1)))
		return (0);
	if (!add_back(&shape, new_cap(shape, -1)))
		return (0);
	return (1);
}

int	parse_plane(char **line, t_shape *shape)
{
	skip(line);
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
