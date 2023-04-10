/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:47:37 by fael-bou          #+#    #+#             */
/*   Updated: 2023/04/10 19:54:08 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "light.h"
#include "camera.h"
#include "shape.h"
#include <math.h>

t_light	*new_light(t_point origine, t_vec color)
{
	t_light	*light;

	light = (t_light *)malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->o = origine;
	light->color = color;
	return (light);
}

int	intersect_light(t_ray ray, t_shape *shape, double distance)
{
	t_equation	e;

	while (shape)
	{
		e = shape->intersection(ray, shape);
		if (e.delta > EPSILON)
		{
			if ((e.t > EPSILON) && distance > e.t)
				return (0);
		}
		shape = shape->next;
	}
	return (1);
}
