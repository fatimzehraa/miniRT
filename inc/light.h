#ifndef LIGHT_H
# define LIGHT_H

# include "vector.h"
# include "camera.h"

typedef struct	s_light
{
	t_point		o;
	t_vec		dir;
	t_vec		color;
}				t_light;

t_light	*new_light(t_point origine, t_vec color);
int	intersect_light(t_ray ray, t_shape *shape);
#endif
