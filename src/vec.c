#include"vector.h"
#include <stdlib.h>
#include<unistd.h>

t_vec	vec(double x, double y, double z)
{
	t_vec	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec	vec_add(t_vec v1, t_vec v2)
{
	t_vec	v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	return (v);
}

t_vec	vec_sub(t_vec v1, t_vec v2)
{
	t_vec	v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
	return (v);
}

t_vec	vec_mul(t_vec v1, t_vec v2)
{
	t_vec	v;

	v.x = v1.x * v2.x;
	v.y = v1.y * v2.y;
	v.z = v1.z * v2.z;
	return (v);
}

t_vec vec_muln(t_vec v1, double num)
{
	t_vec v;
	v.x = v1.x * num;
	v.y = v1.y * num;
	v.z = v1.z * num;
	return (v);
}

t_vec	vec_div(t_vec v1, t_vec v2)
{
	t_vec	v;
	if (v2.x == 0 || v2.y == 0 || v2.z == 0)
		exit(1);
	v.x = v1.x / v2.x;
	v.y = v1.y / v2.y;
	v.z = v1.z / v2.z;
	return (v);
}

double vec_dot(t_vec v1, t_vec v2)
{
	double	v;

	v = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (v);
}

double magnitude(t_vec v)
{
	double	m;

	m = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
	return (m);
}

t_vec norm(t_vec v1)
{
	t_vec v;
	v.x = v1.x/magnitude(v1);
	v.y = v1.y/magnitude(v1);
	v.z = v1.z/magnitude(v1);
	return (v);
}

double vec_rgv(t_vec v)
{
	double color;
	color = 0 | ( (int)(v.x * 255) << 16 | (int)(v.y * 255) << 8 | (int)v.z * 255)/255;
	return (color);
}
