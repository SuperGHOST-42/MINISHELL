/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:17:06 by hgutterr          #+#    #+#             */
/*   Updated: 2026/01/16 17:17:06 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_env	*env_new(char *key, char *value)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (!new->key)
	{
		free(new);
		return (NULL);
	}
	if (value)
	{
		new->value = ft_strdup(value);
		if (!new->value)
		{
			free(new->key);
			free(new);
			return (NULL);
		}
		new->has_value = 1;
	}
	else
	{
		new->value = NULL;
		new->has_value = 0;
	}
	new->next = NULL;
	return (new);
}

static void	env_add_back(t_env **env, t_env *new)
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

t_env	*env_init(char **envp)
{
	t_env	*env;
	char	*equal;
	char	*key;
	char	*value;
	int		i;

	env = NULL;
	if (!envp)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		equal = ft_strchr(envp[i], '=');
		if (equal)
		{
			key = ft_substr(envp[i], 0, equal - envp[i]);
			value = ft_strdup(equal + 1);
			if (key && value)
				env_add_back(&env, env_new(key, value));
			free(key);
			free(value);
		}
		else
			env_add_back(&env, env_new(envp[i], NULL));
	}
	return (env);
}

char	*get_env(t_env *env, const char *key)
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
