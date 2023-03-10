#ifndef CAMERA_H
# define CAMERA_H

#include "minirt.h"
# include "vector.h"
typedef struct	s_camera
{
	t_point	o;
	t_vec	forward;
	double	angle;// /zoom out \zoom in
	double		h;
	double		w;
}				t_camera;

typedef struct	s_ray
{
	t_point	o;
	t_vec	dir;
}				t_ray;

t_camera	camera(t_point origin, t_vec forward, double fov);
t_ray	ray(t_camera cam, t_point p);
double ft_map(double x, double from1, double to1, double from2, double to2);
t_point	pixel_to_point(t_camera cam, int x, int y);
t_pixel point_to_pixel(t_camera cam, t_point p);
void send_ray(t_camera cam, int x, int y, void *mlx, void *win);
void draw(t_camera cam, void *mlx, void *win);
void sphere(t_sphere s, t_camera cam, void *mlx, void *win);
int intersect(t_ray r, t_sphere s, t_camera cam, int x, int y, void *mlx, void *win);
//int intersect(double a, double b, double c, int x, int y);
#endif
