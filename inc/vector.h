#ifndef VECTOR_H
# define VECTOR_H
#include <math.h>
#include<mlx.h>
#include <stdlib.h>
#include<unistd.h>

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}				t_vec;

typedef t_vec t_point;

typedef struct s_pixel{
	int x;
	int y;
} t_pixel;

typedef struct s_line{
	double	a;
	double	b; 
} t_line;

typedef struct s_sphere{
	t_point o;
	double r;
} t_sphere;

t_vec	vec(double x, double y, double z);
t_vec	vec_add(t_vec v1, t_vec v2);
t_vec	sub(t_point v1, t_point v2);
t_vec	vec_sub(t_vec v1, t_vec v2);
t_vec	vec_mul(t_vec v1, t_vec v2);
t_vec	vec_muln(t_vec v1, double num);
t_vec	vec_div(t_vec v1, t_vec v2);
double	vec_dot(t_vec v1, t_vec v2);
t_vec	vec_cross(t_vec v1, t_vec v2);
double	magnitude(t_vec v);
t_vec	norm(t_vec v1);
#endif
