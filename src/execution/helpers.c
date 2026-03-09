/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 15:05:00 by ariclenes         #+#    #+#             */
/*   Updated: 2026/03/09 21:13:36 by arpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minishell_parse.h"

char	*ft_readline(void)
{
	char	cwd[BUFSIZ];
	char	*prompt;
	char	*line;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		rl_already_prompted = 0;
		return (readline(" > "));
	}
	prompt = ft_strjoin(cwd, " > ");
	if (!prompt)
	{
		rl_already_prompted = 0;
		return (readline(" > "));
	}
	rl_already_prompted = 0;
	line = readline(prompt);
	free(prompt);
	return (line);
}

void	error_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

static void	close_if_open(int fd)
{
	int	fd_check;

	fd_check = dup(fd);
	if (fd_check < 0)
		return ;
	close(fd_check);
	close(fd);
}

void	child_cleanup_exit(t_shell *shell, int status)
{
	if (shell)
	{
		if (shell->cmd_head)
			free_cmds(shell->cmd_head);
		free_env(shell->env);
		free(shell);
	}
	close_if_open(STDIN_FILENO);
	close_if_open(STDOUT_FILENO);
	close_if_open(STDERR_FILENO);
	exit(status);
}
