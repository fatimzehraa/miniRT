#ifndef VECTOR_H
# define VECTOR_H
#include <math.h>
#include<mlx.h>

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}				t_vec;



t_vec	vec(double x, double y, double z);
t_vec	vec_add(t_vec v1, t_vec v2);
t_vec	vec_sub(t_vec v1, t_vec v2);
t_vec	vec_mul(t_vec v1, t_vec v2);
t_vec vec_muln(t_vec v1, double num);
t_vec	vec_div(t_vec v1, t_vec v2);
double vec_dot(t_vec v1, t_vec v2);
double magnitude(t_vec v);
t_vec norm(t_vec v1);
#endif
