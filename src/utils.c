#include "minirt.h"
#include "camera.h"

int equal(double a, double b)
{
	return fabs(a - b) <= 0.5;
}

long rgb(double r, double g, double b){
	long color;
	color = 0 | ( (unsigned char)(r * 255) << 16 | (unsigned char)(g * 255) << 8 | (unsigned char)(b * 255));
	return color;
}

t_point get_point(t_ray r, double t)
{
	t_point p;
	p.x = r.o.x + t * r.dir.x;
	p.y = r.o.y + t * r.dir.y;
	p.z = r.o.z + t * r.dir.z;
	return p;
}
