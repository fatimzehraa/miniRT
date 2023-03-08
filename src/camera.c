#include "minirt.h"
#include "camera.h"

t_camera	camera(t_point origin, t_vec forward, double fov)
{
	t_camera	cam;
	cam.o = origin;
	cam.forward = forward;
	cam.angle = fov;
	cam.h = tan(fov / 2);
	cam.w = cam.h * WIN_SIDE / WIN_SIDE;
	return (cam);
}



int ft_map(int x, int from1, int to1, int from2, int to2)
{
	return (x - from1) * (to2 - from2) / (to1 - from1) + from2;
}
