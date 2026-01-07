/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:11:50 by hgutterr          #+#    #+#             */
/*   Updated: 2026/01/07 16:33:13 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO:
// handle || && |(end) cases

#include "../includes/minishell.h"
#include <readline/readline.h>

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
	shell.env = env;
	minishell(&shell);
}
