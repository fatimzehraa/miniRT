//#include "minirt.h"
#include "camera.h"

t_camera	camera(t_vec origin, t_vec forward, double fov)
{
	t_camera	cam;
	cam.origin = origin;
	cam.forward = forward;
	cam.fov = fov;
	return (cam);
}

int ft_map(int x, int from1, int to1, int from2, int to2)
{
	return (x - from1) * (to2 - from2) / (to1 - from1) + from2;
}
