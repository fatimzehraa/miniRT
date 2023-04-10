/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 22:02:36 by fael-bou          #+#    #+#             */
/*   Updated: 2023/04/09 22:46:03 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include "shape.h"
#include "parse.h"
#include "minirt.h"
#include "get_next_line.h"
#include "vector.h"

/* Enum ?
* if res == 1   => ok
* if res == 0   => allocation failed
* if res == -1  => type didn't match
* if res == -2  => duplicated
* **/

int	match(t_ctx *ctx, char *line)
{
	int	res;

	if (line[0] == '\0' || line[0] == '#')
		return (1);
	res = parse_shape(ctx, line);
	if (res != -1)
		return (res);
	res = parse_camera(ctx, line);
	if (res != -1)
		return (res);
	res = parse_light(ctx, line);
	if (res != -1)
		return (res);
	res = parse_ambient(ctx, line);
	return (res);
}

void	reset_ctx(t_ctx *ctx)
{
	ctx->amb = NULL;
	ctx->cam = NULL;
	ctx->lights = NULL;
	ctx->s = NULL;
}

int	parse(char *filename, t_ctx *ctx)
{
	int		fd;
	char	*line;
	int		res;

	reset_ctx(ctx);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		line[ft_strlen(line) - 1] = '\0';
		res = match(ctx, line);
		if (!print_err(res, fd, line))
			return (free(line), free_ctx(ctx), 0);
		free(line);
	}
	return (close(fd), 1);
}
