/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariclenes <ariclenes@student.42lisboa.com> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 15:05:00 by ariclenes         #+#    #+#             */
/*   Updated: 2026/03/08 15:05:00 by ariclenes        ###   ########.fr       */
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

void	child_cleanup_exit(t_shell *shell, int status)
{
	if (shell)
	{
		if (shell->cmd_head)
			free_cmds(shell->cmd_head);
		free_env_exec(shell->env);
		free(shell);
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(status);
}
