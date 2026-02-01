/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:00:00 by hgutterr          #+#    #+#             */
/*   Updated: 2026/01/30 19:00:00 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_env_var(char *var, t_env **env)
{
	char	*equal;
	char	*key;
	char	*value;

	equal = ft_strchr(var, '=');
	if (equal)
	{
		key = ft_substr(var, 0, equal - var);
		value = ft_strdup(equal + 1);
		if (key && value)
			env_add_back(env, env_new(key, value));
		free(key);
		free(value);
	}
	else
		env_add_back(env, env_new(var, NULL));
}

t_env	*env_init(char **envp)
{
	t_env	*env;
	int		i;

	env = NULL;
	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		process_env_var(envp[i], &env);
		i++;
	}
	return (env);
}

char	*env_get(t_env *env, const char *key)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
