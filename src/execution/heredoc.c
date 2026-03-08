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
#include <termios.h>

void	run_heredoc_child(t_redirs *redir, t_shell *shell, int write_fd);
int		wait_heredoc_process(pid_t pid, int read_fd,
			struct termios *saved_term, int has_term);

static pid_t	spawn_heredoc(t_redirs *redir, t_shell *shell, int pfd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		setup_child_signals();
		close(pfd[0]);
		run_heredoc_child(redir, shell, pfd[1]);
	}
	return (pid);
}

static int	fill_heredoc(t_redirs *redir, t_shell *shell)
{
	int				pfd[2];
	pid_t			pid;
	int				status;
	struct termios	saved_term;
	int				has_term;

	has_term = (tcgetattr(STDIN_FILENO, &saved_term) == 0);
	if (pipe(pfd) < 0)
		return (perror("pipe"), 1);
	pid = spawn_heredoc(redir, shell, pfd);
	if (pid < 0)
		return (close(pfd[0]), close(pfd[1]), perror("fork"), 1);
	close(pfd[1]);
	status = wait_heredoc_process(pid, pfd[0], &saved_term, has_term);
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
