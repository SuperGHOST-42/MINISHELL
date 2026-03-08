/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exec_access.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariclenes <ariclenes@student.42lisboa.com> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 15:20:00 by ariclenes         #+#    #+#             */
/*   Updated: 2026/03/08 15:20:00 by ariclenes        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_exec(t_env *env, const char *key)
{
	t_env	*cur;

	if (!key)
		return (NULL);
	cur = env;
	while (cur)
	{
		if (cur->key && ft_strncmp(cur->key, key, ft_strlen(key) + 1) == 0)
		{
			if (cur->value)
				return (cur->value);
			return (NULL);
		}
		cur = cur->next;
	}
	return (NULL);
}

void	free_env_exec(t_env *env)
{
	t_env	*current;
	t_env	*temp;

	current = env;
	while (current)
	{
		temp = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = temp;
	}
}
