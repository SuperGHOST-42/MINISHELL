/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariclenes <ariclenes@student.42lisboa.com> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 15:05:00 by ariclenes         #+#    #+#             */
/*   Updated: 2026/03/08 15:05:00 by ariclenes        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	run_heredoc_child(t_redirs *redir, t_shell *shell, int write_fd);
int		wait_heredoc_process(pid_t pid, int read_fd);

static int	heredoc_error(char *msg, int pfd[2], int close_pipe)
{
	if (close_pipe)
	{
		close(pfd[0]);
		close(pfd[1]);
	}
	perror(msg);
	return (1);
}

static pid_t	spawn_heredoc(t_redirs *redir, t_shell *shell, int pfd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signals_child();
		close(pfd[0]);
		run_heredoc_child(redir, shell, pfd[1]);
	}
	return (pid);
}

static int	start_heredoc(t_redirs *redir, t_shell *shell,
		int pfd[2], pid_t *pid)
{
	if (pipe(pfd) < 0)
		return (heredoc_error("pipe", pfd, 0));
	*pid = spawn_heredoc(redir, shell, pfd);
	if (*pid < 0)
		return (heredoc_error("fork", pfd, 1));
	close(pfd[1]);
	return (0);
}

static int	fill_heredoc(t_redirs *redir, t_shell *shell)
{
	int				pfd[2];
	pid_t			pid;
	int				status;

	if (start_heredoc(redir, shell, pfd, &pid))
		return (1);
	status = wait_heredoc_process(pid, pfd[0]);
	if (status)
		return (status);
	if (redir->heredoc_fd >= 0)
		close(redir->heredoc_fd);
	redir->heredoc_fd = pfd[0];
	return (0);
}

int	prepare_heredoc(t_cmd *cmds, t_shell *shell)
{
	t_redirs	*redir;
	int			status;

	while (cmds)
	{
		redir = cmds->redirs;
		while (redir)
		{
			if (redir->type == R_HEREDOC)
			{
				status = fill_heredoc(redir, shell);
				if (status)
					return (status);
			}
			redir = redir->next;
		}
		cmds = cmds->next;
	}
	return (0);
}
