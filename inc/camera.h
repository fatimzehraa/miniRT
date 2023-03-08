#ifndef CAMERA_H
# define CAMERA_H

#include "minirt.h"
# include "vector.h"
typedef struct	s_camera
{
	t_point	o;
	t_vec	forward;
	double	angle;// /zoom out \zoom in
	int		h;
	int		w;
}				t_camera;

typedef struct	s_ray
{
	t_point	o;
	t_vec	dir;
}				t_ray;

#endif
