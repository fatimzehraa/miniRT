#ifndef CAMERA_H
# define CAMERA_H

# include "vector.h"

typedef struct s_shape	t_shape;

/*
 * angle: zoom out \zoom in
 * */

/*
 * angle: zoom out \zoom in
 * */

typedef struct	s_camera
{
	t_point	o;
	t_vec	forward;
	t_vec	right;
	t_vec	up;
	double	angle;
	double		h;
	double		w;
}				t_camera;

typedef struct s_ray
{
	t_point	o;
	t_vec	dir;
}	t_ray;

typedef struct s_equation
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	t1;
	double	t2;
	double	t;
	t_vec	p_shape;
	t_ray	r_light;
	t_shape	*shape;
}	t_equation;

t_point		get_point(t_ray r, double t);
t_camera	camera(t_point origin, t_vec forward, double fov, t_vec random);
t_ray		ray(t_point o, t_point p);
double		ft_map(double x, double from2, double to2);
t_point		pixel_to_point(t_camera cam, int x, int y);
t_pixel		point_to_pixel(t_camera cam, t_point p);
void		sphere(t_sphere s, t_camera cam, void *mlx, void *win);
t_equation	intersection(t_ray r, t_sphere s);
#endif
