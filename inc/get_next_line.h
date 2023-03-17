/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fael-bou <fael-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 21:14:31 by fael-bou          #+#    #+#             */
/*   Updated: 2023/03/17 03:04:44 by iait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include<unistd.h>
# include<stdlib.h>

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2);
void	ft_strncpy(char *dst, char *src, size_t n);
int		is_new_line(char *s);

# define BUFFER_SIZE 100
#endif
