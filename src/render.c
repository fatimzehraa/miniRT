#include<mlx.h>
#include<stdio.h>
long rgb(unsigned char r, unsigned char g, unsigned char b){
	long color;
	color = 0 | ( r << 16 | g << 8 | b);
	//printf("%d ", color);
	return color;
}
# define WIN_SIDE 1000
typedef	struct s_point{
	double x;
	double y;
	double z;
} t_point;

int sqr(int x)
{
	return x * x;
}

typedef struct s_line{
	int	a;
	int	b; 
} t_line;

t_line	line(t_point p1, t_point p2)
{
	t_line line;
	line.a = (p2.y - p1.y)/(p2.x - p1.x);
	line.b = p1.y - line.a * p1.x;
	return (line);
}

void draw_line(t_line line, void *mlx, void *win)
{
	int x;
	int y;

	y = 0;
	while (y < WIN_SIDE) {
		x = 0;
		while (x < WIN_SIDE) {
			if (y == line.a * x + line.b)
				mlx_pixel_put(mlx, win, x, y, 0xFFFFFF);
			x++;
		}
		y++;
	}
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
	mlx = mlx_init();
	win = mlx_new_window(mlx, WIN_SIDE, WIN_SIDE, "miniRT");
	draw_line(line((t_point){0, 0, 0}, (t_point){WIN_SIDE, WIN_SIDE, 0}), mlx, win);
	draw_line(line((t_point){WIN_SIDE, 0, 0}, (t_point){0, WIN_SIDE, 0}), mlx, win);
	//circle(center, 50, mlx, win);
	//render(mlx, win);
	mlx_loop(mlx);

	return (0);
}
