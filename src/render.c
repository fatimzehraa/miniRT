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

	center.x = WIN_SIDE/2;
	center.y = WIN_SIDE/2;
	mlx = mlx_init();
	win = mlx_new_window(mlx, WIN_SIDE, WIN_SIDE, "miniRT");
	circle(center, 50, mlx, win);
	//render(mlx, win);
	mlx_loop(mlx);

	return (0);
}
