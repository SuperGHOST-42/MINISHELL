/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:50:32 by hgutterr          #+#    #+#             */
/*   Updated: 2026/02/03 11:46:59 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_sig;

char	*builtin_to_str(t_builtin builtin);
char	*token_to_str(t_token_type type);

void	test_args_builtins_env(t_cmd *cmds, t_shell *shell)
{
	int	cmd_num;

	cmd_num = 0;
	while(cmds)
	{
		printf("Command %d:\n", cmd_num);
		if (cmds->args)
		{
			int i = 0;
			while (cmds->args[i])
			{
				
				/*-------------------CHECK EXPANSION-------------------*/
				if (cmds->args[i][0] == '$')
				{
					t_env *env = shell->env;
					while (env)
					{
						if (strcmp(cmds->args[i] + 1, env->key) == 0)
						{
							printf("2  Arg[%d]: %s=%s\n", i, cmds->args[i], env->value);
							break ;
						}
						env = env->next;
					}
				}
				/*------------------------------------------------------*/

				else
				printf("  Arg[%d]: %s\n", i, cmds->args[i]);
				i++;
			}
			printf("  Builtin: %s\n", builtin_to_str(cmds->builtin));
			if (cmds->redirs)
			{
				t_redirs *redir = cmds->redirs;
				while (redir)
				{
					printf("  Redir: Type %s, Target %s\n", token_to_str(redir->type), redir->target);
					redir = redir->next;
				}
			}
			else
				printf("  No redirections.\n");
		}
		else
			printf("  No arguments.\n");
		printf("\n");
		cmds = cmds->next;
		cmd_num++;
	}
}
char	*builtin_to_str(t_builtin builtin)
{
	if (builtin == BI_ECHO)
		return ("BI_ECHO");
	if (builtin == BI_CD)
		return ("BI_CD");
	if (builtin == BI_PWD)
		return ("BI_PWD");
	if (builtin == BI_EXPORT)
		return ("BI_EXPORT");
	if (builtin == BI_UNSET)
		return ("BI_UNSET");
	if (builtin == BI_ENV)
		return ("BI_ENV");
	if (builtin == BI_EXIT)
		return ("BI_EXIT");
	return ("BI_NONE");
}

char	*token_to_str(t_token_type type)
{
	if (type == WORD)
		return ("WORD");
	if (type == PIPE)
		return ("PIPE");
	if (type == R_IN)
		return ("R_IN");
	if (type == R_OUT)
		return ("R_OUT");
	if (type == R_APP)
		return ("R_APP");
	if (type == R_HEREDOC)
		return ("R_HEREDOC");
	return ("UNKNOWN");
}
/*--------------------------------------------------------------------------------*/

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
		//test_args_builtins_env(cmds, shell);
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
