/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:49:52 by hgutterr          #+#    #+#             */
/*   Updated: 2026/02/03 12:27:48 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_builtin	get_builtin_type(const char *cmd)
{
	if (!cmd)
		return (BI_NONE);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (BI_ECHO);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (BI_CD);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (BI_PWD);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (BI_EXPORT);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (BI_UNSET);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (BI_ENV);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (BI_EXIT);
	return (BI_NONE);
}

int	ft_env(t_shell *shell)
{
	t_env	*current;

	if (!shell || !shell->env)
		return (1);
	current = shell->env;
	while (current)
	{
		if (current->has_value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}

int	ft_exit(t_shell *shell, char *exit_code_str)
{
	int	exit_code;

	exit_code = 0;
	if (exit_code_str)
		exit_code = ft_atoi(exit_code_str);
	if (shell)
	{
		shell->should_exit = 1;
		shell->exit_code = exit_code;
	}
	return (exit_code);
}
