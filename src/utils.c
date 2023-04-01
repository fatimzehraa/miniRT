#include "minirt.h"
#include "camera.h"

int	equal(double a, double b)
{
	return (fabs(a - b) <= 0.5);
}

long	rgb(double r, double g, double b)
{
	long	color;

	if (r > 1 || r < 0)
		r = r > 1;
	if (g > 1 || g < 0)
		g = g > 1;
	if (b > 1 || b < 0)
		b = b > 1;
	color = 0 | (((unsigned char)(r * 255)) << 16
			| ((unsigned char)(g * 255)) << 8 | (unsigned char)(b * 255));
	return (color);
}

t_point	get_point(t_ray r, double t)
{
	t_point	p;

	p.x = r.o.x + t * r.dir.x;
	p.y = r.o.y + t * r.dir.y;
	p.z = r.o.z + t * r.dir.z;
	return (p);
}
