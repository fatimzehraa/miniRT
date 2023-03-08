#include "minirt.h"
#include<mlx.h>
#include<stdio.h>
long rgb(unsigned char r, unsigned char g, unsigned char b){
	long color;
	color = 0 | ( r << 16 | g << 8 | b);
	//printf("%d ", color);
	return color;
}
int sqr(int x)
{
	return x * x;
}

typedef struct s_line{
	double	a;
	double	b; 
} t_line;

t_line	line(t_point p1, t_point p2)
{
	t_line line;
	line.a = (p2.y - p1.y)/(p2.x - p1.x);
	line.b = p1.y - line.a * p1.x;
	return (line);
}

int distance(t_point p1, t_point p2)
{
	return (sqr(p2.x - p1.x) + sqr(p2.y - p1.y));
}

int between(t_point p1, t_point p2, t_point p)
{
	if (distance(p1, p2) == distance(p1, p) + distance(p2, p))
		return (1);
//	if (p.x > p1.x && p.x < p2.x && p.y > p1.y && p.y < p2.y)
//		return (1);
	return (0);
}

#include <math.h>

int equal(double a, double b)
{
	return fabs(a - b) <= 0.5;
}

void draw_line(t_line line, t_point p1, t_point p2, void *mlx, void *win)
{
	int x;
	int y;

	y = 0;
	while (y < WIN_SIDE) { 
		x = 0;
		while (x < WIN_SIDE) {
			if (equal(y, line.a * x + line.b) && (between(p1, p2, (t_point){x, y, 0})))// || between(p2, p1, (t_point){x, y, 0})))
			{
				mlx_pixel_put(mlx, win, x, y, 0xFFFFFF);
				break;
			}
			x++;
		}
		y++;
	}
}

void draw_triangle(t_point p1, t_point p2, t_point p3, void *mlx, void *win)
{
	(void)p2;
//	draw_line(line(p1, p2), p1, p2, mlx, win);
//	draw_line(line(p2, p3), p2, p3, mlx, win);
	draw_line(line(p3, p1), p3, p1, mlx, win);
}

void circle(t_point center, int r, void *mlx, void *win){
	int x;
	int y;

	y = 0;
	while (y < WIN_SIDE) {
		x = 0;
		while (x < WIN_SIDE) {
			if (sqr(x - center.x) + sqr(y - center.y) > sqr(r))
				//mlx_pixel_put(mlx, win, x, y, rgb((x)*255/WIN_SIDE,  (WIN_SIDE - y) * 255/WIN_SIDE, 0));
				mlx_pixel_put(mlx, win, x, y, 0xFFFFFF);
			x++;
		}
		y++;
	}
}

void render(void *mlx, void *win)
{
	int x;
	int y;

	y = 0;
	while(y < WIN_SIDE){
		x = 0;
		while (x < WIN_SIDE) {
			mlx_pixel_put(mlx, win, x, y, rgb((x)*255/WIN_SIDE,  (WIN_SIDE - y) * 255/WIN_SIDE, 0));
			x++;
		}
		y++;
	}

}

int main(void)
{
	void *win;
	void *mlx;
	 t_point center;

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
//	draw_triangle(center, p1, p2, mlx, win);
	draw_line(line(p2, center), p2, center, mlx, win);
//	draw_line(line((t_point){WIN_SIDE, 0, 0}, (t_point){0, WIN_SIDE, 0}), mlx, win);
	//circle(center, 50, mlx, win);
	//render(mlx, win);
	mlx_loop(mlx);

	return (0);
}
