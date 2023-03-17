#ifndef PARSE_H
# define PARSE_H

# include "vector.h"
# include "shape.h"
# include "minirt.h"

int	parse_vec(char **p, t_vec *v);
int parse_float(char **p, double *d);
int parse_color(char **p, t_vec *color);
int skip(char **p);
int	is_same(char **line, const char *s2);
int	parse(char *filename, t_ctx *ctx);

#endif
