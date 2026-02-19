#include "../../includes/minishell.h"

static void	run_child(t_cmd *cmd, t_shell *shell);

void	exec_child(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;	

	pid = fork();
	if (pid < 0)
		error_exit("fork");
	if (pid == 0)
		run_child(cmd, shell);
	if (waitpid(pid, &status, 0) < 0)
	{
		perror("waitpid");
		shell->last_status = 1;
		return ;
	}
	shell->last_status = status_to_exit_code(status);
}

static void	run_child(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	char	**envp;

	if (!cmd)
		exit(1);
	if (apply_redirs(cmd->redirs))
		exit(1);
	if (!cmd->args || !cmd->args[0])
		exit(0);
	if (is_builtin(cmd))
		exit(exec_builtin(cmd, shell));
	envp = env_to_envp(shell->env);
	if (!envp)
		exit(1);
	path = resolve_path(shell->env, cmd->args[0]);
	if (!path)
	{
		perror(cmd->args[0]);
		free_envp(envp);
		exit(127);
	}
	execve(path, cmd->args, envp);
	perror(path);
	free(path);
	free_envp(envp);
	if (errno == ENOENT)
		exit(127);
	exit(126);
}
