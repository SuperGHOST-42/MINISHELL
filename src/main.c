#include "../includes/minishell.h"

void	parser(t_cmd *cmd)
{
	cmd->args = malloc(sizeof(char *) * 3);
	if(cmd->args == NULL)
		error_exit("Malloc failed");
	
	cmd->args[0] = ft_strdup("/bin/ls");
	cmd->args[1] = ft_strdup("Makefile");
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
		exec_pipeline(cmd, shell);
	}
	else if (cmd->builtin != BI_NONE && is_parent_needed(cmd->builtin))
	{
		shell->last_status = exec_builtin(cmd, shell);
	}
	else
	{
		create_process(cmd, shell);
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
	
	shell->envp = envp;

	init_shell(shell);
	
	free(shell);
	return (EXIT_SUCCESS);
}
