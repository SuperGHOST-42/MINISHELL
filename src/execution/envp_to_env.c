/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_to_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:17:06 by hgutterr          #+#    #+#             */
/*   Updated: 2026/03/10 17:17:14 by arpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	set_env_value(t_env *new, char *value)
{
	if (!value)
	{
		new->value = NULL;
		new->has_value = 0;
		return (0);
	}
	new->value = ft_strdup(value);
	if (!new->value)
		return (1);
	new->has_value = 1;
	return (0);
}

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
	if (set_env_value(new, value))
	{
		free(new->key);
		free(new);
		return (NULL);
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

static int	add_env_entry(t_env **env, char *entry, char *key
	, char *equal)
{
	char	*tmp;
	t_env	*new;

	equal = ft_strchr(entry, '=');
	if (equal)
	{
		key = ft_substr(entry, 0, equal - entry);
		if (!key)
			return (1);
		if (ft_strncmp(key, "SHLVL", 5) == 0)
		{
			tmp = ft_itoa(ft_atoi(equal + 1));
			new = env_new(key, tmp + 1);
			free(tmp);
		}
		else
			new = env_new(key, equal + 1);
		free(key);
	}
	else
		new = env_new(entry, NULL);
	if (!new)
		return (1);
	env_add_back(env, new);
	return (0);
}

t_env	*envp_to_env(char **envp)
{
	t_env	*env;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		if (add_env_entry(&env, envp[i], NULL, NULL))
		{
			free_env(env);
			return (NULL);
		}
		i++;
	}
	return (env);
}
