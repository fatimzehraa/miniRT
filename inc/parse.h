#ifndef PARSE_H
# define PARSE_H

# include "vector.h"
# include "shape.h"
# include "minirt.h"

int	parse_vec(char **p, t_vec *v);
int	parse_float(char **p, double *d);
int	parse_int(char **p, double *i);
int	parse_color(char **p, t_vec *color);
int	skip(char **p);
int	is_same(char **line, const char *s2);
int	parse_sphere(char **line, t_shape *shape);
int	parse_cy(char **line, t_shape *shape);
int	parse_plane(char **line, t_shape *shape);
int	parse(char *filename, t_ctx *ctx);

#endif
