#include "../includes/minishell.h"

void	parser(t_cmd *cmd)
{
	cmd->args = malloc(sizeof(char *) * 3);
	if(cmd->args == NULL)
		error_exit("Malloc failed");
	
	cmd->args[0] = ft_strdup("ls");
	cmd->args[1] = ft_strdup("test");
	cmd->args[2] = NULL;
	
	cmd->builtin = BI_NONE;
	cmd->pid = -1;
	cmd->redirs = NULL;
	cmd->next = NULL;
}

void	exec_cmd(t_cmd *cmd, t_shell *shell)
{
	if (cmd->next != NULL) //caso há pipe
	{
		printf("entrou 1\n");
		exec_pipeline(cmd, shell);
	}
	else if (is_builtin(cmd) && is_parent_needed(cmd))
	{
		printf("entrou 2\n");
		shell->last_status = exec_builtin(cmd, shell);
	}
	else
	{
		printf("entrou 3\n");
		exec_child(cmd, shell);
	}
	return ;
}

void	init_shell(t_shell *shell)
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
		free(line);
		cmd = malloc(sizeof(t_cmd));
		if (!cmd)
			error_exit("malloc");
		ft_bzero(cmd, sizeof(t_cmd));
		parser(cmd); // hugo
		exec_cmd(cmd, shell);
		free_cmd(cmd);
		printf("last status = %i\n", shell->last_status);
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
	shell->env = env_init(envp);
	if (!shell->env)
		error_exit("env_init");
	init_shell(shell);	
	env_free(shell->env);
	free(shell); // TODO: free_shell();
	return (EXIT_SUCCESS);
}
