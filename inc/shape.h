#ifndef SHAPE_H
# define SHAPE_H

# include "vector.h"
# include "camera.h"

typedef struct s_light t_light;
typedef struct s_shape
{
	t_vec			color;
	t_point			origin;
	t_vec			forward;
	double			r;
	double			height;
	double			d3;
	t_vec			(*normal_at)(t_point p, struct s_shape	*s);
	t_equation		(*intersection)(t_ray r, struct s_shape	*s);
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

#endif
