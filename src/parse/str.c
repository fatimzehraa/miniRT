/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:47:14 by fael-bou          #+#    #+#             */
/*   Updated: 2023/04/09 21:55:04 by fael-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stddef.h>
#include <stdio.h>

#include "get_next_line.h"

int	is_same(char **line, const char *s2)
{
	size_t	i;
	size_t	n;
	char	*s1;

	n = ft_strlen(s2);
	s1 = *line;
	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	*line += n;
	return (1);
}

int	skip(char **p)
{
	if (**p != ' ')
		return (0);
	while (**p == ' ')
		(*p)++;
	return (1);
}

int	print_err(int res, int fd, char *line)
{
	if (res == 0)
	{
		printf("miniRT: failed to parse line or allocate memory `%s`\n", line);
		close(fd);
		return (0);
	}
	if (res == -1)
	{
		printf("miniRT: failed to parse line `%s` \n", line);
		close(fd);
		return (0);
	}
	if (res == -2)
	{
		printf("miniRT: duplicated element `%s` \n", line);
		close(fd);
		return (0);
	}
	if (res == -3)
	{
		printf("miniRT: extra chars at end of line `%s` \n", line);
		close(fd);
		return (0);
	}
	return (1);
}
