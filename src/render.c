#include "camera.h"
#include "light.h"
#include "shape.h"
#include "minirt.h"
#include "vector.h"
#include<mlx.h>
#include<stdio.h>
#include <math.h>

t_vec put_color(t_ray r, t_ctx ctx)
{
	t_equation e;
	t_equation e_min;
	t_shape *s = ctx.s;

	e_min.t = INFINITY;
	e_min.shape = NULL;
	while (s)
	{
		e = s->intersection(r, s);
		if (e.delta >= 0)
		{
			e.p_shape = vec_add(vec_muln(r.dir, e.t), r.o);
			e.r_light = ray(e.p_shape, ctx.lights->o);
			if (e.t > 0 && e_min.t >= e.t)
				e_min = e;
		}
		s = s->next;
	}
	if (e_min.t == INFINITY || !intersect_light(e_min.r_light, ctx.s))
		return ((t_vec){0,0,0});
	double cos = vec_dot(e_min.r_light.dir, e_min.shape->normal_at(e.p_shape, e_min.shape) );
	if (cos < 0)
		return ((t_vec){0,0,0});
	return (vec_muln(e_min.shape->color, cos));

	//return (e_min.shape->color);
}

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


void render_(t_ctx ctx)
{
	t_ray r;
	t_vec color;
	t_data data;

	data.img = mlx_new_image(ctx.mlx, WIN_SIDE, WIN_SIDE);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	ctx.y = 0;
	while (ctx.y < WIN_SIDE)
	{
		ctx.x = 0;
		while (ctx.x < WIN_SIDE)
		{
			ctx.p.x = ft_map(ctx.x, 0, WIN_SIDE, -ctx.cam->w, ctx.cam->w);
			ctx.p.y = ft_map(ctx.y, 0, WIN_SIDE, ctx.cam->h, -ctx.cam->h);

			r.o = ctx.cam->o;
			r.dir = vec_add(ctx.cam->forward, vec_add(vec_muln(ctx.cam->up, ctx.p.y), vec_muln(ctx.cam->right, ctx.p.x)));
			r.dir = norm(r.dir);
			color = put_color(r, ctx);
			my_mlx_pixel_put(&data, ctx.x, ctx.y, rgb(color.x, color.y, color.z));
			ctx.x++;
		}
		ctx.y++;
	}
	mlx_put_image_to_window(ctx.mlx, ctx.win, data.img, 0, 0);
}
