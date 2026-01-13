#include "../includes/minishell.h"

char	*ft_readline(void)
{
	char	cwd[BUFSIZ];
	char	*prompt;
	char	*line;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		printf("error getcwd\n");
		return (readline(" > "));
	}
	prompt = ft_strjoin(cwd, " > ");
	line = readline(prompt);
	free(prompt);
	return (line);
}
void	parser(t_cmd *cmd)
{
	cmd->args = malloc(sizeof(char *) * 3);
	if(cmd->args == NULL)
		error_exit("Malloc failed");
	cmd->args[0] = ft_strdup("/bin/echo");
	cmd->args[1] = ft_strdup("Hello World");
	cmd->args[2] = NULL;
	cmd->builtin = BI_ECHO;
	cmd->pid = -1;
	cmd->redirs = NULL;
	cmd->next = NULL;
}

void	create_process(t_cmd *cmd, t_shell *shell, char **env)
{
	pid_t	pid;
	int		ret;
	int		status;

	pid = fork();
	if (pid < 0)
		error_exit("fork");
	if (pid == 0)
	{
		if (cmd->builtin != BI_NONE)
		{
			ret = exec_builtin(cmd);
			printf("entrou 2\n");
			exit(ret);
		}
		printf("entrou 3\n");
		execve(cmd->args[0], cmd->args, env);
		error_exit("execve");
		exit(127);
	}
	else
	{
		waitpid(pid, &status, 0);
		shell->exit_code = status_to_exit_code(status);
	}
}

int	exec_cmd(t_cmd *cmd, t_shell *shell, char **env)
{
	pid_t	pid;
	int		ret;

	if (cmd->builtin != BI_NONE && is_parent_needed(cmd->builtin))
	{
		ret = exec_builtin(cmd);
		printf("entrou 1\n");
	}
	else
	{
		printf("create process\n");
		create_process(cmd, shell, env);
	}
	return (0);
}

void	init_shell(char **env)
{
	char	*line;
	t_cmd	*cmd;
	t_shell *shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		error_exit("malloc");
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
		parser(cmd); // hugo
		////////////////////
		exec_cmd(cmd, shell, env);
		free_cmd(cmd);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_cmd	*cmd;
	t_env	*envp;
	t_shell	*shell = NULL;

	(void)argc;
	(void)argv;
	(void)envp;
	
	init_shell(env);
	perror(""); 
	return (EXIT_SUCCESS);
}
