/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:11:50 by hgutterr          #+#    #+#             */
/*   Updated: 2026/01/10 02:01:57 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO:
// handle || && |(end) cases

#include "../includes/minishell.h"

volatile sig_atomic_t	g_sig;

void	minishell(t_shell *shell)
{
	char *line;
	while(1)
	{
		line = readline("$> ");
		if (!line)
		{
			rl_clear_history();
			exit(0);
		}
		accept_line(shell, line);
		free(line);
	}

}
int	main(int argc, char **argv, char **env)
{
	t_shell shell;

	if(argc != 1)
		return (-1);
	(void)argv;
	(void)argc;
	shell.env = NULL;
	shell.last_status = 0;
	shell.should_exit = 0;
	shell.exit_code = 0;
	minishell(&shell);
}
