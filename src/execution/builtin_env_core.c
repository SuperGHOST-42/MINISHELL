/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_core.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghost <ghost@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 20:10:00 by ghost             #+#    #+#             */
/*   Updated: 2026/02/19 20:10:00 by ghost            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin_helpers.h"

int	bt_key_match(const char *a, const char *b)
{
	if (!a || !b)
		return (0);
	return (ft_strncmp((char *)a, (char *)b, ft_strlen((char *)b) + 1) == 0);
}

t_env	*bt_find_env(t_env *env, const char *key)
{
	while (env)
	{
		if (bt_key_match(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

t_env	*bt_new_env_node(const char *key, const char *value, int has_value)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup((char *)key);
	if (!new->key)
		return (free(new), NULL);
	new->has_value = has_value;
	if (has_value)
	{
		new->value = ft_strdup((char *)value);
		if (!new->value)
			return (free(new->key), free(new), NULL);
	}
	return (new);
}

int	bt_append_env(t_env **env, t_env *new)
{
	t_env	*cur;

	if (!env || !new)
		return (1);
	if (!*env)
	{
		*env = new;
		return (0);
	}
	cur = *env;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
	return (0);
}

int	bt_set_env_value(t_env **env, const char *key, const char *value)
{
	t_env	*node;
	char	*dup;

	node = bt_find_env(*env, key);
	if (node)
	{
		dup = ft_strdup((char *)value);
		if (!dup)
			return (1);
		free(node->value);
		node->value = dup;
		node->has_value = 1;
		return (0);
	}
	node = bt_new_env_node(key, value, 1);
	if (!node)
		return (1);
	return (bt_append_env(env, node));
}
