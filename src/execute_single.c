# include "../includes/minishell.h"

int	status_to_exit_code(int status)
{
	int	sig;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		return (128 + sig);
	}
	return (1);
}

int	is_parent_needed(t_builtin bi)
{
	if (bi == BI_CD)
		return (1);
	if (bi == BI_EXIT)
		return (1);
	if (bi == BI_EXPORT)
		return (1);
	if (bi == BI_UNSET)
		return (1);
	return (0);
}

int exec_builtin(t_cmd *cmd, t_shell *shell)
{
	(void)cmd;
	(void)shell;
	printf("exec_builtin executed\n");
	return (77);
}

void	create_process(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		error_exit("fork");
	if (pid == 0)
	{
		if (cmd->builtin != BI_NONE)
			exit(exec_builtin(cmd, shell));
		path = resolve_path(shell->envp, cmd->args[0]);
		if (!path)
		{
			perror(cmd->args[0]);
			exit(127); //command not found
		}
		execve(path, cmd->args, shell->envp);
		perror(path);
		free(path);
		exit(126); //command found, permission denied
	}
	else
	{
		if (waitpid(pid, &status, 0) < 0)
		{
			perror("waitpid");
			shell->last_status = 1;
			return ;
		}
		shell->last_status = status_to_exit_code(status);
	}
}
