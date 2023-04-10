/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 20:48:09 by fael-bou          #+#    #+#             */
/*   Updated: 2023/04/10 00:10:19 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H

# include "vector.h"
# include "camera.h"

typedef struct s_light	t_light;
typedef struct s_shape
{
	t_vec			color;
	t_point			origin;
	t_vec			forward;
	double			r;
	double			height;
	double			d3;
	t_vec			(*normal_at)();
	t_equation		(*intersection)();
	t_vec			u;
	t_vec			v;
	struct s_shape	*next;
}	t_shape;

t_shape		*lst_new(void);
int			add_back(t_shape **lst, t_shape *new);
t_shape		*new_sphere(t_point origin, double r);
t_vec		sp_normal_at(t_point p, t_shape *s);
void		circle(t_point center, int r, void *mlx, void *win);
t_shape		*new_plane(t_point p, t_vec v);
t_vec		pl_normal_at(t_point p, t_shape *s);
t_shape		*new_cap(t_shape *cy, int dir);
t_shape		*new_cylinder(t_point p, t_vec v, double r, double h);
t_vec		cy_normal_at(t_point p, t_shape *s);
t_equation	plane_intersection(t_ray r, t_shape *s);
t_equation	sphere_intersection(t_ray r, t_shape *s);
t_equation	cylinder_intersection(t_ray r, t_shape *s);
t_light		*ft_lstlast_light(t_light *lst);
int			add_back_light(t_light **lst, t_light *new);
t_shape		*new_sq_cap(t_vec v);
t_equation	sq_intersection(t_ray r, t_shape *s);
void		first_sqcap(t_shape *shape, t_shape *def);
t_shape	*new_cub_cap(t_shape *orshape, t_shape *s, int dir, int i);
t_equation	cap_intersection(t_ray r, t_shape *s);
t_vec		get_random_forward(t_vec v);
t_equation	no_intersection(t_ray r, t_shape *s);

#endif
