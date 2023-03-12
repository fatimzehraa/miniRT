#ifndef SHAPE_H
# define SHAPE_H

#include "vector.h"
#include "camera.h"
#include "minirt.h"


typedef struct s_shape {
	t_vec			color;
	t_point			origin;

	double			d1;
	double			d2;
	double			d3;

	t_vec			(*normal_at)();
	t_equation		(*intersection)();

	struct s_shape	*next;
} t_shape;

t_shape *new_sphere(t_point origin, double r);

#endif
