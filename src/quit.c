/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:45:05 by fael-bou          #+#    #+#             */
/*   Updated: 2023/04/09 21:45:38 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_shapes(t_shape *s)
{
	t_shape	*tmp;

	while (s)
	{
		tmp = s;
		s = s->next;
		free(tmp);
	}
	s = NULL;
}

void	free_lights(t_light *l)
{
	t_light	*tmp;

	while (l)
	{
		tmp = l;
		l = l->next;
		free(tmp);
	}
	l = NULL;
}

void	free_ctx(t_ctx *ctx)
{
	if (!ctx)
		return ;
	if (ctx->s)
		free_shapes(ctx->s);
	if (ctx->lights)
		free_lights(ctx->lights);
	if (ctx->cam)
		free(ctx->cam);
	if (ctx->win)
		mlx_destroy_window(ctx->mlx, ctx->win);
}

int	key_hook(int keycode, t_ctx *ctx)
{
	if (keycode == 53)
	{
		free_ctx(ctx);
		exit(0);
	}
	return (0);
}

int	quit(t_ctx *ctx)
{
	free_ctx(ctx);
	exit(0);
}
