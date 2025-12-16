/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:11:50 by hgutterr          #+#    #+#             */
/*   Updated: 2025/12/16 18:18:57 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void parce_cmd(char *line)
// {
// 	char *temp;
// 	while (line)
// 	{
		
// 	}
	
// }

void	accept_line(char *line)
{
	if (ft_isempty(line))
		return ;
	add_history(line);
	printf("%s\n", line);
	// parce_cmd(line); // TODO
}
void	minishell(char **env)
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
		accept_line(line);
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
