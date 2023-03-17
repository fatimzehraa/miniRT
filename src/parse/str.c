#include<stddef.h>

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
