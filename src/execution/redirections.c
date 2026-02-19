#include "../../includes/minishell.h"

static int	dup_target_fd(t_redirs *redir)
{
	if (redir->type == R_IN || redir->type == R_HEREDOC)
		return (STDIN_FILENO);
	return (STDOUT_FILENO);
}

static int	open_redir_fd(t_redirs *redir)
{
	if (!redir || !redir->target)
		return (-1);
	if (redir->type == R_IN)
		return (open(redir->target, O_RDONLY));
	if (redir->type == R_OUT)
		return (open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (redir->type == R_APP)
		return (open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (-1);
}

static int	apply_one_redir(t_redirs *redir)
{
	int	fd;

	if (!redir)
		return (0);
	if (redir->type == R_HEREDOC)
	{
		if (redir->heredoc_fd < 0)
			return (1);
		fd = redir->heredoc_fd;
		redir->heredoc_fd = -1;
	}
	else
	{
		fd = open_redir_fd(redir);
		if (fd < 0)
		{
			perror(redir->target);
			return (1);
		}
	}
	if (dup2(fd, dup_target_fd(redir)) < 0)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static int	apply_redirs_rec(t_redirs *redirs)
{
	if (!redirs)
		return (0);
	if (apply_redirs_rec(redirs->next))
		return (1);
	return (apply_one_redir(redirs));
}

int	apply_redirs(t_redirs *redirs)
{
	return (apply_redirs_rec(redirs));
}
