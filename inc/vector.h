/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:48:19 by fael-bou          #+#    #+#             */
/*   Updated: 2023/04/09 21:50:08 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>
# include<mlx.h>
# include <stdlib.h>
# include<unistd.h>

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef t_vec	t_point;

typedef struct s_pixel
{
	int	x;
	int	y;
}	t_pixel;

typedef struct s_line
{
	double	a;
	double	b;
}	t_line;

typedef struct s_sphere
{
	t_point	o;
	double	r;
}	t_sphere;

t_vec	vec(double x, double y, double z);
t_vec	add(t_vec v1, t_vec v2);
t_vec	sub(t_point v1, t_point v2);
t_vec	vsub(t_vec v1, t_vec v2);
t_vec	mul(t_vec v1, t_vec v2);
t_vec	muln(t_vec v1, double num);
t_vec	vdiv(t_vec v1, t_vec v2);
double	dot(t_vec v1, t_vec v2);
t_vec	cross(t_vec v1, t_vec v2);
double	magnitude(t_vec v);
int		cmp(t_vec v1, t_vec v2);
t_vec	norm(t_vec v1);
t_vec	reflect(t_vec v, t_vec n);

#endif
