#include "minirt.h"
#include "vector.h"
#include <mlx.h>
#include "camera.h"

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
	forward.x = 0;
	forward.y = 0;
	forward.z = 1;

	cam = camera(o, forward, 90);
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
	sphere(center, 50, cam, mlx, win);
	sphere(o, 150, cam, mlx, win);
//	draw(cam, mlx, win);
//	draw_triangle(center, p1, p2, mlx, win);
//	draw_line(line(p2, center), p2, center, mlx, win);
//	draw_line(line((t_point){WIN_SIDE, 0, 0}, (t_point){0, WIN_SIDE, 0}), mlx, win);
	//circle(center, 50, mlx, win);
	//render(mlx, win);
	mlx_loop(mlx);

	return (0);
}
