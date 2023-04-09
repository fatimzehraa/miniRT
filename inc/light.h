/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:47:56 by fael-bou          #+#    #+#             */
/*   Updated: 2023/04/09 21:47:57 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "vector.h"
# include "camera.h"

typedef struct s_light
{
	t_point			o;
	t_vec			dir;
	t_vec			color;
	double			ratio;
	struct s_light	*next;
}				t_light;

t_light	*new_light(t_point origine, t_vec color);
int		intersect_light(t_ray ray, t_shape *shape, double distance);
#endif
