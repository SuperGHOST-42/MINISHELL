# include "../includes/minishell.h"

int	stack_size(t_cmd *cmd)
{
	int	size;

	size = 0;
	while (cmd)
	{
		size++;
		cmd = cmd->next;
	}
	return (size); 
}

t_cmd	*ft_new_node(void)
{
	t_cmd *new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	ft_bzero(new, sizeof(t_cmd));
	return (new);
}

void	ft_lstadd_front(t_cmd **list, t_cmd *new)
{
	if (!list || !new)
		return ;
	new->next = *list;
	*list = new;
}

void	ft_lstadd_back(t_cmd **list, t_cmd *new)
{
	t_cmd	*ptr;

	if (!list || !new)
		return ;
	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	ptr = *list;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}