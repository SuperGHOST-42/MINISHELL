#include "../../includes/execute_pipeline_utils.h"

int	pipe_prepare(int fd[2], int has_next)
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

void	close_fd(int fd)
{
	if (fd >= 0)
		close(fd);
}

int	dup_prepare(int fd[2], int prev_fd, int has_next)
{
	if (prev_fd >= 0)
	{
		if (dup2(prev_fd, STDIN_FILENO) < 0)
		{
			close_fd(fd[0]);
			close_fd(fd[1]);
			perror("dup2 stdin");
			return (-1);
		}
		close_fd(prev_fd);
	}
	if (has_next)
	{
		if (dup2(fd[1], STDOUT_FILENO) < 0)
		{
			close_fd(fd[0]);
			close_fd(fd[1]);
			perror("dup2 stdout");
			return (-1);
		}
		close_fd(fd[0]);
		close_fd(fd[1]);
	}
	return (0);
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
