#ifndef MINIRT_H
# define MINIRT_H

# include "vector.h"
# define WIN_SIDE 1000

long rgb(unsigned char r, unsigned char g, unsigned char b);
void render(void *mlx, void *win);
void circle(t_point center, int r, void *mlx, void *win);
void draw_triangle(t_point p1, t_point p2, t_point p3, void *mlx, void *win);
void draw_line(t_line line, t_point p1, t_point p2, void *mlx, void *win);
int equal(double a, double b);
int distance(t_point p1, t_point p2);
int between(t_point p1, t_point p2, t_point p);

#endif
