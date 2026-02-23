/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_unset.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghost <ghost@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 20:10:00 by ghost             #+#    #+#             */
/*   Updated: 2026/02/19 20:10:00 by ghost            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin_helpers.h"

static void	print_export_list(t_env *env)
{
	while (env)
	{
		if (env->has_value)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
}

static int	export_arg(t_shell *shell, char *arg)
{
	char	*eq;
	char	*key;

	if (!bt_is_valid_export(arg))
		return (bt_print_id_error("export", arg));
	eq = ft_strchr(arg, '=');
	if (!eq)
		return (bt_ensure_env_key(&shell->env, arg));
	key = ft_substr(arg, 0, eq - arg);
	if (!key)
		return (1);
	if (bt_set_env_value(&shell->env, key, eq + 1))
	{
		free(key);
		return (1);
	}
	free(key);
	return (0);
}

int	ft_export(t_shell *shell, char **args)
{
	int	i;
	int	status;

	if (!shell || !args)
		return (1);
	if (!args[1])
		return (print_export_list(shell->env), 0);
	i = 1;
	status = 0;
	while (args[i])
		status |= export_arg(shell, args[i++]);
	return (status);
}

int	ft_unset(t_shell *shell, char **args)
{
	int	i;
	int	status;

	if (!shell || !args)
		return (1);
	i = 1;
	status = 0;
	while (args[i])
	{
		if (!bt_is_valid_key(args[i]))
			status = bt_print_id_error("unset", args[i]);
		else
			bt_remove_env_key(&shell->env, args[i]);
		i++;
	}
	return (status);
}
