#include "vector.h"
#include "shape.h"
#include <stdio.h>
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
