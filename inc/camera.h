#ifndef CAMERA_H
# define CAMERA_H

# include "vector.h"
typedef struct	s_camera
{
	t_vec	origin;
	t_vec	forward;
	int		fov;// /zoom out \zoom in
}				t_camera;

#endif
