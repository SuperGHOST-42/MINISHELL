/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:11:50 by hgutterr          #+#    #+#             */
/*   Updated: 2025/12/16 17:38:15 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parce_cmd(char *line)
{
	printf("%s\n", line);
}
void	minishell(char **env)
{
	char *line;
	while(1)
	{
		line = readline("$> ");
		if (!line)
		{
			printf("y");
			rl_clear_history();
			free(line);
			exit(0);
		}
		add_history(line);
		parce_cmd(line); // TODO
		free(line);
	}
}


int	main(int argc, char **argv, char **env)
{
	if(argc != 1)
		return (-1);
	(void)argv;
	(void)argc;
	minishell(env);
	return (0);
}
