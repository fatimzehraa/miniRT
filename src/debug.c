#include "vector.h"
#include "shape.h"
#include <stdio.h>
#include "camera.h"
#include "light.h"
#include "minirt.h"

void print_vec(t_vec *vec)
{
	printf("x: %f, y: %f, z: %f", vec->x, vec->y, vec->z);
}


void print_shape(t_shape *shape)
{
	printf(" ======= SHAPE ==========\n");
	printf("origin:");
	print_vec(&shape->origin);

	printf("\nforward:");
	print_vec(&shape->forward);

	printf("\ncolor:");
	print_vec(&shape->color);

	printf("\nr: %f, height: %f\n", shape->r, shape->height);
	printf("\n");
}	

void print_cam(t_camera *cam)
{
	printf(" ======= CAM ==========\n");
	printf("origin:");
	print_vec(&cam->o);

	printf("\nforward:");
	print_vec(&cam->forward);

	printf("\nup:");
	print_vec(&cam->up);

	printf("\nright:");
	print_vec(&cam->right);

	printf("\nwidth: %f, height: %f", cam->w, cam->h);

	printf("\nfov: %f\n", cam->angle);
	printf("\n");
}

void print_light(t_light *light)
{
	printf(" ======= LIGHT ==========\n");
	printf("origin:");
	print_vec(&light->o);

	printf("\ncolor:");
	print_vec(&light->color);

	printf("\nintensity: %f\n", light->ratio);

	printf("\n");
}

void print_ctx(t_ctx ctx)
{
	print_cam(ctx.cam);
	print_light(ctx.lights);
	t_shape *s = ctx.s;
	while (s)
	{
		print_shape(s);
		s = s->next;
	}
}
