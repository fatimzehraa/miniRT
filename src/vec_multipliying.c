/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_multipliying.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:46:06 by fael-bou          #+#    #+#             */
/*   Updated: 2023/04/09 21:46:08 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec	mul(t_vec v1, t_vec v2)
{
	t_vec	v;

	v.x = v1.x * v2.x;
	v.y = v1.y * v2.y;
	v.z = v1.z * v2.z;
	return (v);
}

t_vec	muln(t_vec v1, double num)
{
	t_vec	v;

	v.x = v1.x * num;
	v.y = v1.y * num;
	v.z = v1.z * num;
	return (v);
}

t_vec	vdiv(t_vec v1, t_vec v2)
{
	t_vec	v;

	if (v2.x == 0 || v2.y == 0 || v2.z == 0)
		exit(1);
	v.x = v1.x / v2.x;
	v.y = v1.y / v2.y;
	v.z = v1.z / v2.z;
	return (v);
}

double	dot(t_vec v1, t_vec v2)
{
	double	v;

	v = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (v);
}

t_vec	cross(t_vec v1, t_vec v2)
{
	t_vec	v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}
