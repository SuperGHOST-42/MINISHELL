#include "../../includes/minishell.h"

static void	close_fd(int fd)
{
	if (fd >= 0)
		close(fd);
}

static int	pipe_prepare(int fd[2], int has_next)
{
	fd[0] = -1;
	fd[1] = -1;
	if (!has_next)
		return (0);
	if (pipe(fd) < 0)
		return (perror("pipe"), -1);
	return (0);
}

static pid_t	fork_or_error(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror("minishell: fork");
	return (pid);
}

static void	child_setup_io(int prev_read, int fd[2], int has_next)
{
	if (prev_read >= 0)
	{
		if (dup2(prev_read, STDIN_FILENO) < 0)
		{
			perror("dup2 stdin");
			exit(1);
		}
		close_fd(prev_read);
	}
	if (has_next)
	{
		if (dup2(fd[1], STDOUT_FILENO) < 0)
		{
			perror("dup2 stdout");
			exit(1);
		}
		close_fd(fd[0]);
		close_fd(fd[1]);
	}
}

static void	parent_keep_fds(int *prev_read, int fd[2], int has_next)
{
	close_fd(*prev_read);
	if (has_next)
	{
		close_fd(fd[1]);
		*prev_read = fd[0];
	}
	else
		close_fd(fd[0]);
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
	if (cmd->builtin != BI_NONE)
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

static int	wait_all(t_cmd *cmds, pid_t last_pid)
{
	int		st;
	int		last;

	last = 0;
	while (cmds)
	{
		waitpid(cmds->pid, &st, 0);
		if (cmds->pid == last_pid)
			last = st;
		cmds = cmds->next;
	}
	if (WIFEXITED(last))
		return (WEXITSTATUS(last));
	if (WIFSIGNALED(last))
		return (128 + WTERMSIG(last));
	return (1);
}

void	exec_pipeline(t_cmd *cmds, t_shell *shell)
{
	int		prev_read;
	int		fd[2];
	pid_t	pid;
	pid_t	last_pid;
	t_cmd	*cur;

	prev_read = -1;
	last_pid = -1;
	cur = cmds;
	while (cur)
	{
		if (pipe_prepare(fd, (cur->next != NULL)) < 0)
			return ;
		pid = fork_or_error();
		if (pid < 0)
			return ;
		if (pid == 0)
		{
			child_setup_io(prev_read, fd, (cur->next != NULL));
			run_child(cur, shell);
		}
		cur->pid = pid;
		last_pid = pid;
		parent_keep_fds(&prev_read, fd, (cur->next != NULL));
		cur = cur->next;
	}
	close_fd(prev_read);
	shell->last_status = wait_all(cmds, last_pid);
}
