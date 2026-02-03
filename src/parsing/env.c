/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:50:51 by hgutterr          #+#    #+#             */
/*   Updated: 2026/01/30 18:50:51 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minishell_parse.h"

static int	set_env_key(t_env *new, char *key)
{
	new->key = ft_strdup(key);
	if (!new->key)
	{
		free(new);
		return (0);
	}
	return (1);
}

static int	set_env_value(t_env *new, char *value)
{
	if (value)
	{
		new->value = ft_strdup(value);
		if (!new->value)
		{
			free(new->key);
			free(new);
			return (0);
		}
		new->has_value = 1;
	}
	else
	{
		new->value = NULL;
		new->has_value = 0;
	}
	return (1);
}

t_env	*env_new(char *key, char *value)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	if (!set_env_key(new, key))
		return (NULL);
	if (!set_env_value(new, value))
		return (NULL);
	new->next = NULL;
	return (new);
}

void	env_add_back(t_env **env, t_env *new)
{
	t_env	*current;

	if (!env || !new)
		return ;
	if (!(*env))
	{
		*env = new;
		return ;
	}
	current = *env;
	while (current->next)
		current = current->next;
	current->next = new;
}
