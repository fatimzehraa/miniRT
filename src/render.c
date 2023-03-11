#include "camera.h"
#include "minirt.h"
#include "vector.h"
#include<mlx.h>
#include<stdio.h>
long rgb(unsigned char r, unsigned char g, unsigned char b){
	long color;
	color = 0 | ( r << 16 | g << 8 | b);
	return color;
}

int distance(t_point p1, t_point p2)
{
	return (pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
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

t_line	line(t_point p1, t_point p2)
{
	t_line line;
	line.a = (p2.y - p1.y)/(p2.x - p1.x);
	line.b = p1.y - line.a * p1.x;
	return (line);
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
	draw_line(line(p1, p2), p1, p2, mlx, win);
	draw_line(line(p2, p3), p2, p3, mlx, win);
	draw_line(line(p3, p1), p3, p1, mlx, win);
}

void circle(t_point center, int r, void *mlx, void *win){
	int x;
	int y;

	y = 0;
	while (y < WIN_SIDE) {
		x = 0;
		while (x < WIN_SIDE) {
			if (pow(x - center.x, 2) + pow(y - center.y, 2) > pow(r, 2))
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

void sphere(t_sphere s, t_camera cam, void *mlx, void *win)
{
	int x;
	int y;
	t_ray r;
	t_point p;
	t_equation e;
// 
	y = 0;
	while (y < WIN_SIDE) {
		x = 0;
		while (x < WIN_SIDE) {
			p.x = ft_map(x, 0, WIN_SIDE, -cam.w, cam.w);
			p.y = ft_map(y, 0, WIN_SIDE, cam.h, -cam.h);
			r = ray(cam, p);
			e = intersection(r, s);
			if (e.delta < 0)
;//				mlx_pixel_put(mlx, win, x, y, 0x000000);
			else
		 		mlx_pixel_put(mlx, win, x, y, rgb(ft_map(r.dir.x, cam.h, -cam.h, 0, 1)*255, 0, ft_map(r.dir.y, -cam.h, cam.h, 0, 1) * 255));
			x++;
		}
		y++;
	}
}
