#include "../../includes/minishell.h"
#include "../../includes/minishell_parse.h"

char	*builtin_to_str(t_builtin builtin);
char	*token_to_str(t_token_type type);

static void print_cmds(t_cmd *cmds, t_shell *shell)
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
							printf("  Arg[%d]: %s=%s\n", i, cmds->args[i], env->value);
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

static void	exec_cmd(t_cmd *cmd, t_shell *shell)
{
	if (cmd->next != NULL)
	exec_pipeline(cmd, shell);
	else if (is_builtin(cmd) && is_parent_needed(cmd))
	shell->last_status = exec_builtin(cmd, shell);
	else
	exec_child(cmd, shell);
	return ;
}

static void	init_shell(t_shell *shell)
{
	char	*line;
	t_cmd	*cmd;
	
	while (1)
	{
		line = ft_readline();
		if (line == NULL)
		break;
		else
		add_history(line);
		cmd = malloc(sizeof(t_cmd));
		if (!cmd)
		error_exit("malloc");
		ft_bzero(cmd, sizeof(t_cmd));
		
		cmd = parse(shell, line);
		free(line);
		
		print_cmds(cmd, shell);
		//exec_cmd(cmd, shell);
		
		free_cmds(cmd);
		if (shell->should_exit != 0)
		break ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		error_exit("malloc");
	
	ft_bzero(shell, sizeof(t_shell));

	shell->env = env_init_exec(envp);
	if (!shell->env)
		error_exit("env_init");
	
	init_shell(shell);	
	
	free_env_exec(shell->env);
	free(shell); // fazer: free_shell();
	
	return (shell->exit_code);
}