/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariclenes <ariclenes@student.42lisboa.com> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 15:20:00 by ariclenes         #+#    #+#             */
/*   Updated: 2026/03/08 15:20:00 by ariclenes        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_parent_needed(t_cmd *cmd)
{
	if (!cmd)
		return (0);
	if (cmd->builtin == BI_CD)
		return (1);
	if (cmd->builtin == BI_EXIT)
		return (1);
	if (cmd->builtin == BI_EXPORT)
		return (1);
	if (cmd->builtin == BI_UNSET)
		return (1);
	return (0);
}

int	is_builtin(t_cmd *cmd)
{
	if (cmd->builtin != BI_NONE)
		return (1);
	return (0);
}

int	status_to_exit_code(int status)
{
	int	sig;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		return (128 + sig);
	}
	return (1);
}
