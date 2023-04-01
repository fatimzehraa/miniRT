#ifndef MINIRT_H
# define MINIRT_H

# include "camera.h"
# include "light.h"
# include "shape.h"
# include "vector.h"

# define WIN_SIDE 1000
# define EPSILON 0.001

typedef struct s_ctx
{
	void		*mlx;
	void		*win;
	t_shape		*s;
	t_camera	*cam;
	t_light		*lights;
	int			x;
	int			y;
	t_point		p;
}	t_ctx;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

long	rgb(double r, double g, double b);
int		equal(double a, double b);
void	render_(t_ctx ctx);
// todo: delete
void	print_shape(t_shape *shape);
void	print_vec(t_vec *vec);
void	print_ctx(t_ctx ctx);

#endif
