#include "shape.h"
#include <stdlib.h>

t_shape	*ft_lstlast(t_shape *lst)
{
	t_shape	*cur;
	t_shape	*last;

	cur = lst;
	last = lst;
	while (cur)
	{
		last = cur;
		cur = cur->next;
	}
	return (last);
}

t_shape *lst_new()
{
	t_shape	*lst;

	lst = malloc(sizeof(t_shape));
	if (lst == NULL)
		return (NULL);
	lst->next = NULL;
	return (lst);
}

int	add_back(t_shape **lst, t_shape *new)
{
	t_shape	*last;

	if (new == NULL)
		return (0);
	if (*lst == 0)
	{
		*lst = new;
		return (1);
	}
	last = ft_lstlast(*lst);
	last->next = new;
	return (1);
}

