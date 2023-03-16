#include "minirt.h"
#include "light.h"
#include "camera.h"
#include "shape.h"

t_light	*new_light(t_point origine, t_vec color)
{
	t_light	*light;

	light = (t_light *)malloc(sizeof(t_light));
	light->o = origine;
	light->color = color;
	return (light);
}

int	intersect_light(t_ray ray, t_shape *shape)
{
	t_equation e;

	while (shape)
	{
		e = shape->intersection(ray, shape);
		if (e.delta > 0)
		{
			if (e.t1 > EPSILON || e.t2 > EPSILON)
				return (0);
		}
		shape = shape->next;
	}
	return (1);
}
