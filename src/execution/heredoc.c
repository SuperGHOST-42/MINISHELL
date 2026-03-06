#include "../../includes/minishell.h"
#include "../../includes/minishell_parse.h"
#include <termios.h>

static int	write_line(int fd, char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (write(fd, line, len) < 0)
		return (1);
	if (write(fd, "\n", 1) < 0)
		return (1);
	return (0);
}

static char	*expand_line(t_shell *shell, char *line)
{
	t_token	*tok;
	char	*new_line;

	tok = new_token(WORD, ft_strdup(line));
	if (!tok)
		return (NULL);
	if (!tok->value || expand_tokens(shell, tok))
	{
		free_tokens(tok);
		return (NULL);
	}
	new_line = ft_strdup(tok->value);
	free_tokens(tok);
	return (new_line);
}

static int	process_line(t_redirs *redir, t_shell *shell, int fd, char *line)
{
	char	*tmp;

	if (redir->expand)
	{
		tmp = expand_line(shell, line);
		free(line);
		line = tmp;
		if (!line)
			return (1);
	}
	if (write_line(fd, line))
	{
		free(line);
		return (1);
	}
	free(line);
	return (0);
}

int		heredoc_child(t_redirs *redir, t_shell *shell, int write_fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, redir->target,
				ft_strlen(redir->target) + 1) == 0)
		{
			free(line);
			break ;
		}
		if (process_line(redir, shell, write_fd, line))
		{
			close(write_fd);
			return (1);
		}
	}
	close(write_fd);
	return (0);
}

static void	reset_readline_state(void)
{
	setup_interactive_signals();
}

static int	wait_status(int status, int read_fd)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (write(STDOUT_FILENO, "\n", 1), close(read_fd), 130);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		return (write(STDOUT_FILENO, "\n", 1), close(read_fd), 130);
	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		return (close(read_fd), 1);
	return (0);
}

static int	wait_heredoc(pid_t pid, int read_fd,
		struct termios *saved_term, int has_term)
{
	int	status;

	setup_wait_signals();
	if (waitpid(pid, &status, 0) < 0)
	{
		reset_readline_state();
		if (has_term)
			tcsetattr(STDIN_FILENO, TCSANOW, saved_term);
		close(read_fd);
		perror("waitpid");
		return (1);
	}
	reset_readline_state();
	if (has_term)
		tcsetattr(STDIN_FILENO, TCSANOW, saved_term);
	return (wait_status(status, read_fd));
}

static pid_t	spawn_heredoc(t_redirs *redir, t_shell *shell, int pfd[2], t_cmd *cmds)
{
	pid_t	pid;
	int r;

	pid = fork();
	if (pid == 0)
	{
		setup_child_signals();
		close(pfd[0]);
		r = heredoc_child(redir, shell, pfd[1]);
		free_cmds(cmds);
		free_env_exec(shell->env);
		free(shell);
		exit(r);
	}
	return (pid);
}

static int	fill_heredoc(t_redirs *redir, t_shell *shell, t_cmd *cmds)
{
	int				pfd[2];
	pid_t			pid;
	int				status;
	struct termios	saved_term;
	int				has_term;
	has_term = (tcgetattr(STDIN_FILENO, &saved_term) == 0);
	if (pipe(pfd) < 0)
		return (perror("pipe"), 1);
	pid = spawn_heredoc(redir, shell, pfd, cmds);
	if (pid < 0)
		return (close(pfd[0]), close(pfd[1]), perror("fork"), 1);
	close(pfd[1]);
	status = wait_heredoc(pid, pfd[0], &saved_term, has_term);
	if (status)
		return (status);
	if (redir->heredoc_fd >= 0)
		close(redir->heredoc_fd);
	redir->heredoc_fd = pfd[0];
	return (0);
}

int	prepare_heredoc(t_cmd *cmds, t_shell *shell)
{
	t_redirs	*redir;
	int			status;
	
	while (cmds)
	{
		redir = cmds->redirs;
		while (redir)
		{
			if (redir->type == R_HEREDOC)
			{
				status = fill_heredoc(redir, shell, cmds);
				if (status)
					return (status);
			}
			redir = redir->next;
		}
		cmds = cmds->next;
	}
	return (0);
}
