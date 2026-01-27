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

static void	run_child(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	char	**envp;

	if (is_builtin(cmd))
		exit(exec_builtin(cmd, shell));
	envp = env_to_envp(shell->env);
	if (!envp)
		exit(1);
	path = resolve_path(shell->env, cmd->args[0]);
	if (!path)
	{
		perror(cmd->args[0]);
		free(envp);
		exit(127);
	}
	execve(path, cmd->args, envp);
	perror(path);
	free(path);
	free(envp);
	if (errno == ENOENT)
		exit(127);
	exit(126);
}

void	exec_child(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;
	int		wait_pid;

	pid = fork();
	if (pid < 0)
		error_exit("fork");
	if (pid == 0)
		run_child(cmd, shell);
	wait_pid = waitpid(pid, &status, 0);
	if (wait_pid < 0)
	{
		perror("waitpid");
		shell->last_status = 1;
		return ;
	}
	shell->last_status = status_to_exit_code(status);
}

