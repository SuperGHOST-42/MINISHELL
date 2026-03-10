/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 15:05:00 by ariclenes         #+#    #+#             */
/*   Updated: 2026/03/10 01:49:22 by arpereir         ###   ########.fr       */
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
		signals_child();
		run_child(cmd, shell);
	}
	signals_wait();
	if (waitpid(pid, &status, 0) < 0)
	{
		perror("waitpid");
		signals_prompt();
		shell->last_status = 1;
		return ;
	}
	signals_prompt();
	shell->last_status = status_to_exit_code(status);
}

static void	run_child(t_cmd *cmd, t_shell *shell)
{
	int	status;

	if (!cmd)
		child_cleanup_exit(shell, 1);
	if (apply_redirs(cmd->redirs))
		child_cleanup_exit(shell, 1);
	if (!cmd->args || !cmd->args[0])
		child_cleanup_exit(shell, 0);
	if (is_builtin(cmd))
	{
		status = exec_builtin(cmd, shell);
		child_cleanup_exit(shell, status);
	}
	exec_external_cmd(cmd, shell);
	child_cleanup_exit(shell, 1);
}
