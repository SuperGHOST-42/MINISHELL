/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariclenes <ariclenes@student.42lisboa.com> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 15:05:00 by ariclenes         #+#    #+#             */
/*   Updated: 2026/03/08 15:05:00 by ariclenes        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	run_child(t_cmd *cmd, t_shell *shell);

void	exec_child(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		error_exit("fork");
	if (pid == 0)
	{
		setup_child_signals();
		run_child(cmd, shell);
	}
	setup_wait_signals();
	if (waitpid(pid, &status, 0) < 0)
	{
		perror("waitpid");
		setup_interactive_signals();
		shell->last_status = 1;
		return ;
	}
	setup_interactive_signals();
	shell->last_status = status_to_exit_code(status);
}

static void	run_child(t_cmd *cmd, t_shell *shell)
{
	if (!cmd)
		child_cleanup_exit(shell, 1);
	if (apply_redirs(cmd->redirs))
		child_cleanup_exit(shell, 1);
	if (!cmd->args || !cmd->args[0])
		child_cleanup_exit(shell, 0);
	if (is_builtin(cmd))
		child_cleanup_exit(shell, exec_builtin(cmd, shell));
	exec_external_cmd(cmd, shell);
	child_cleanup_exit(shell, 1);
}
