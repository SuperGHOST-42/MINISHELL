/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_wait.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariclenes <ariclenes@student.42lisboa.com> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 15:20:00 by ariclenes         #+#    #+#             */
/*   Updated: 2026/03/08 15:20:00 by ariclenes        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	reset_readline_state(void)
{
	signals_prompt();
}

static int	wait_status(int status, int read_fd)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		close(read_fd);
		return (130);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		write(STDOUT_FILENO, "\n", 1);
		close(read_fd);
		return (130);
	}
	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
	{
		close(read_fd);
		return (1);
	}
	return (0);
}

int	wait_heredoc_process(pid_t pid, int read_fd)
{
	int	status;

	signals_wait();
	if (waitpid(pid, &status, 0) < 0)
	{
		reset_readline_state();
		close(read_fd);
		perror("waitpid");
		return (1);
	}
	reset_readline_state();
	return (wait_status(status, read_fd));
}
