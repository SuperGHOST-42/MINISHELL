/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:55:10 by hgutterr          #+#    #+#             */
/*   Updated: 2026/01/30 18:55:10 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*env_dup(t_env *env)
{
	t_env	*new_env;
	t_env	*current;
	t_env	*new_node;

	new_env = NULL;
	current = env;
	while (current)
	{
		new_node = env_new(current->key, current->value);
		if (!new_node)
		{
			env_free(new_env);
			return (NULL);
		}
		env_add_back(&new_env, new_node);
		current = current->next;
	}
	return (new_env);
}

void	env_free(t_env *env)
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
