/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:46:21 by fael-bou          #+#    #+#             */
/*   Updated: 2023/04/09 21:46:22 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec	vec(double x, double y, double z)
{
	t_vec	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

double	magnitude(t_vec v)
{
	double	m;

	m = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
	return (m);
}

t_vec	norm(t_vec v1)
{
	t_vec	v;

	v.x = v1.x / magnitude(v1);
	v.y = v1.y / magnitude(v1);
	v.z = v1.z / magnitude(v1);
	return (v);
}

int	cmp(t_vec v1, t_vec v2)
{
	if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z)
		return (1);
	return (0);
}

int	rgv(t_vec v)
{
	int	color;

	color = 0 | ((int)(v.x * 255) << 16
			| (int)(v.y * 255) << 8 | (int)v.z * 255);
	return (color);
}
