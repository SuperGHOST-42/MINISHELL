/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:49:52 by hgutterr          #+#    #+#             */
/*   Updated: 2026/02/03 13:48:29 by arpereir         ###   ########.fr       */
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

int	ft_env(t_shell *shell, char **args)
{
	t_env	*current;

	if (!shell || !args)
		return (1);
	if (args[1])
	{
		ft_putstr_fd("minishell: env: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (127);
	}
	if (!shell->env)
		return (0);
	current = shell->env;
	while (current)
	{
		if (current->has_value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}
