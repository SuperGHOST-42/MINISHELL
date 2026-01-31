/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:50:32 by hgutterr          #+#    #+#             */
/*   Updated: 2026/01/30 18:50:34 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_sig;

void	minishell(t_shell *shell)
{
	char	*line;
	t_cmd	*cmds;

	while (shell->should_exit == 0)
	{
		line = readline("$> ");
		if (!line)
		{
			rl_clear_history();
			exit(0);
		}
		cmds = parse(shell, line);
		free(line);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	if (argc != 1)
		return (-1);
	(void)argv;
	(void)argc;
	shell.env = env_init(env);
	shell.env_backup = env_dup(shell.env);
	shell.last_status = 0;
	shell.should_exit = 0;
	shell.exit_code = 0;
	minishell(&shell);
	env_free(shell.env);
	env_free(shell.env_backup);
	return (shell.exit_code);
}
