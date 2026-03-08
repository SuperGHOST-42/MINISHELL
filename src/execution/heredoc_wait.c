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
#include <termios.h>

static void	reset_readline_state(void)
{
	setup_interactive_signals();
}

static int	wait_status(int status, int read_fd)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (write(STDOUT_FILENO, "\n", 1), close(read_fd), 130);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		return (write(STDOUT_FILENO, "\n", 1), close(read_fd), 130);
	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		return (close(read_fd), 1);
	return (0);
}

int	wait_heredoc_process(pid_t pid, int read_fd,
		struct termios *saved_term, int has_term)
{
	int	status;

	setup_wait_signals();
	if (waitpid(pid, &status, 0) < 0)
	{
		reset_readline_state();
		if (has_term)
			tcsetattr(STDIN_FILENO, TCSANOW, saved_term);
		close(read_fd);
		perror("waitpid");
		return (1);
	}
	reset_readline_state();
	if (has_term)
		tcsetattr(STDIN_FILENO, TCSANOW, saved_term);
	return (wait_status(status, read_fd));
}
