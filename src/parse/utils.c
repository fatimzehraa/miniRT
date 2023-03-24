#include "minirt.h"

static double _parse_float(char **p, int is_int)
{
	double d;
	double fr;
	char *s;
	int is_neg;

	d = 0;
	s = *p;
	is_neg = (*s == '-' && s++);
	while (*s && *s >= '0' && *s <= '9')
	{
		d = d * 10 + *s - '0';
		s++;
	}
	if (*s == '.' && !is_int)
	{
		s++;
		fr = 0.1;
		while (*s && *s >= '0' && *s <= '9')
		{
			d = d + (*s - '0') * fr;
			fr *= 0.1;
			s++;
		}
	}
	*p = s;
	if (is_neg)
		d = -d;
	return d;
}


int parse_float(char **p, double *d)
{
	if (**p == '\0')
		return (0);
	*d = _parse_float(p, 0);
	if (**p == ' ' || **p == '\0' || **p == ',')
		return (1);
	return (0);
}

int parse_vec(char **p, t_vec *v)
{
	if (!parse_float(p, &v->x))
		return (0);
	if (**p == ',')
		(*p)++;
	else
		return (0);
	if (!parse_float(p, &v->y))
		return (0);
	if (**p == ',')
		(*p)++;
	else
		return (0);
	if (!parse_float(p, &v->z))
		return (0);
	return (1);
}

int skip(char **p)
{
	if (**p != ' ')
		return (0);
	while (**p == ' ')
		(*p)++;
	return (1);
}

int parse_int(char **p, double *i)
{
	if (**p == '\0')
		return (0);
	*i = (int)_parse_float(p, 1);
	if (**p == ' ' || **p == '\0' || **p == ',')
		return (1);
	return (0);
}


int parse_color(char **p, t_vec *color)
{
	if (!parse_int(p, &color->x))
		return (0);
	if (**p == ',')
		(*p)++;
	else
		return (0);
	if (!parse_int(p, &color->y))
		return (0);
	if (**p == ',')
		(*p)++;
	else
		return (0);
	if (!parse_int(p, &color->z))
		return (0);

	if (color->x < 0 || color->x > 255)
		return (0);
	if (color->y < 0 || color->y > 255)
		return (0);
	if (color->z < 0 || color->z > 255)
		return (0);

	color->x = color->x / 255;
	color->y = color->y / 255;
	color->z = color->z / 255;

	return (1);
}