#include "../../includes/minishell.h"

static int	pipe_prepare(int fd[2], int has_next)
{
	fd[0] = -1;
	fd[1] = -1;
	if (!has_next)
		return (0);
	if (pipe(fd) < 0)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

static void	close_fd(int fd)
{
	if (fd >= 0)
		close(fd);
}

static void	clean_fds(int fd[2])
{
	close_fd(fd[0]);
	close_fd(fd[1]);
}

static int	dup_prepare(int fd[2], int prev_fd, int has_next)
{
	if (prev_fd >= 0)
	{
		if (dup2(prev_fd, STDIN_FILENO) < 0)
			return (clean_fds(fd), perror("dup2 stdin"), -1);
		close_fd(prev_fd);
	}
	if (has_next)
	{
		if (dup2(fd[1], STDOUT_FILENO) < 0)
			return (clean_fds(fd), perror("dup2 stdout"), -1);
		close_fd(fd[1]);
		close_fd(fd[0]);
	}
	return (0);
}

static void	execve_fail(char *cmd, char *path, char **envp)
{
	int	code;

	code = 126;
	if (errno == ENOENT)
		code = 127;
	perror(cmd);
	free(path);
	free_envp(envp);
	exit(code);
}

static void	refresh_fds(int *prev_read, int fd[2], int has_next)
{
	close_fd(*prev_read);
	close_fd(fd[1]);
	if (has_next)
		*prev_read = fd[0];
	else
		close_fd(fd[0]);
}

static void	run_external(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	char	**envp;

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
	execve_fail(cmd->args[0], path, envp);
}

static void	run_child(t_cmd *cmd, t_shell *shell)
{
	if (!cmd)
		exit(1);
	if (apply_redirs(cmd->redirs))
		exit(1);
	if (!cmd->args || !cmd->args[0])
		exit(0);
	if (cmd->builtin != BI_NONE)
		exit(exec_builtin(cmd, shell));
	run_external(cmd, shell);
}

static pid_t	open_process(t_cmd *cur, t_shell *shell, int prev_read, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (clean_fds(fd), -1);
	if (pid == 0)
	{
		if (dup_prepare(fd, prev_read, (cur->next != NULL)) < 0)
			exit(1);
		run_child(cur, shell);
	}
	return (pid);
}

static void	wait_pipeline(t_cmd *cmd, t_shell *shell)
{
	int		status;
	t_cmd	*cur;

	cur = cmd;
	while (cur)
	{
		if (cur->pid > 0 && waitpid(cur->pid, &status, 0) > 0)
			shell->last_status = status_to_exit_code(status);
		cur = cur->next;
	}
}

void	exec_pipeline(t_cmd *cmd, t_shell *shell)
{
	int		fd[2];
	int		prev_fd;
	pid_t	pid;
	t_cmd	*cur;

	prev_fd = -1;
	cur = cmd;
	while (cur)
	{
		if (pipe_prepare(fd, (cur->next != NULL)) < 0)
			break ;
		pid = open_process(cur, shell, prev_fd, fd);
		if (pid < 0)
			break ;
		refresh_fds(&prev_fd, fd, (cur->next != NULL));
		cur->pid = pid;
		cur = cur->next;
	}
	close_fd(prev_fd);
	wait_pipeline(cmd, shell);
}
