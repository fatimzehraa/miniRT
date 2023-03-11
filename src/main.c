#include "minirt.h"
#include "vector.h"
#include <mlx.h>
#include "camera.h"
#include <math.h>

typedef struct s_list
{
	void *shape;
	struct s_list *next;
} t_list;

int main(void)
{
	void *win;
	void *mlx;
	 t_point center;
	t_point o;
	t_vec forward;
	t_camera cam;
	o.x = 0;
	o.y = 0;
	o.z = -1;
	forward.x = 500;
	forward.y = 500;
	forward.z = 1;

	cam = camera(o, forward, M_PI/2);
	center.x = (double)WIN_SIDE/2;
	center.y = (double)WIN_SIDE/2; 
	t_point p1;
	t_point p2;
	p1.x = 0;
	p1.y = 0;
	p2.x = 600;
	p2.y = 400;
	mlx = mlx_init();
	win = mlx_new_window(mlx, WIN_SIDE, WIN_SIDE, "miniRT");
	t_sphere s;
	s.o = (t_point){0.5, 0.50, 1};
	s.r = 1;
	t_sphere s1;
	s1.o = (t_point){-1, 1, 0};
	s1.r = 0.5;
	sphere(s1, cam, mlx, win);
	sphere(s, cam, mlx, win);
	mlx_loop(mlx);

	return (0);
}
