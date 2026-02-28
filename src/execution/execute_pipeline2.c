/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghost <ghost@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 20:20:00 by ghost             #+#    #+#             */
/*   Updated: 2026/02/19 20:20:00 by ghost            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute_pipeline_utils.h"

void	refresh_fds(int *prev_read, int fd[2], int has_next)
{
	close_fd(*prev_read);
	close_fd(fd[1]);
	if (has_next)
		*prev_read = fd[0];
	else
		close_fd(fd[0]);
}

static void	run_pipeline_child(t_cmd *cmd, t_shell *shell)
{
	if (!cmd)
		exit(1);
	if (apply_redirs(cmd->redirs))
		exit(1);
	if (!cmd->args || !cmd->args[0])
		exit(0);
	if (cmd->builtin != BI_NONE)
		exit(exec_builtin(cmd, shell));
	exec_external_cmd(cmd, shell);
}

pid_t	open_process(t_cmd *cur, t_shell *shell, int prev_read, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close_fd(fd[0]);
		close_fd(fd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		setup_child_signals();
		if (dup_prepare(fd, prev_read, (cur->next != NULL)) < 0)
			exit(1);
		run_pipeline_child(cur, shell);
	}
	return (pid);
}

void	wait_pipeline(t_cmd *cmd, t_shell *shell)
{
	int		status;
	t_cmd	*cur;

	cur = cmd;
	while (cur)
	{
		if (cur->pid > 0 && waitpid(cur->pid, &status, 0) > 0)
			shell->last_status = status_to_exit_code(status);
		cur = cur->next;
	}
}
