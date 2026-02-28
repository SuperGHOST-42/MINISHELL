#include "../../includes/minishell.h"
#include "../../includes/minishell_parse.h"

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

static int	fill_heredoc(t_redirs *redir, t_shell *shell)
{
	int		pfd[2];
	char	*line;

	if (pipe(pfd) < 0)
		return (perror("pipe"), 1);
	while (1)
	{
		line = readline("> ");
		if (consume_sigint())
			return (free(line), close(pfd[0]), close(pfd[1]), 130);
		if (!line || ft_strncmp(line, redir->target,
				ft_strlen(redir->target) + 1) == 0)
			break ;
		if (process_line(redir, shell, pfd[1], line))
			return (close(pfd[0]), close(pfd[1]), 1);
	}
	free(line);
	if (redir->heredoc_fd >= 0)
		close(redir->heredoc_fd);
	close(pfd[1]);
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
				status = fill_heredoc(redir, shell);
				if (status)
					return (status);
			}
			redir = redir->next;
		}
		cmds = cmds->next;
	}
	return (0);
}
