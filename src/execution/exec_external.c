#include "../../includes/minishell.h"

static int	is_directory(char *path)
{
	struct stat	st;

	if (!path)
		return (0);
	if (stat(path, &st) < 0)
		return (0);
	return (S_ISDIR(st.st_mode));
}

static void	print_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
}

static void	exit_not_found(t_cmd *cmd, char **envp)
{
	if (ft_strchr(cmd->args[0], '/'))
		perror(cmd->args[0]);
	else
		print_not_found(cmd->args[0]);
	free_envp(envp);
	exit(127);
}

static void	exit_is_directory(char *cmd, char *path, char **envp)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": is a directory", 2);
	free(path);
	free_envp(envp);
	exit(126);
}

void	exec_external_cmd(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	char	**envp;

	envp = env_to_envp(shell->env);
	if (!envp)
		exit(1);
	path = resolve_path(shell->env, cmd->args[0]);
	if (!path)
		exit_not_found(cmd, envp);
	if (is_directory(path))
		exit_is_directory(cmd->args[0], path, envp);
	execve(path, cmd->args, envp);
	perror(cmd->args[0]);
	free(path);
	free_envp(envp);
	exit((errno == ENOENT) + 126);
}
