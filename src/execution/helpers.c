#include "../../includes/minishell.h"

char	*ft_readline(void)
{
	char	cwd[BUFSIZ];
	char	*prompt;
	char	*line;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (readline(" > "));
	prompt = ft_strjoin(cwd, " > ");
	if (!prompt)
		return (readline(" > "));
	line = readline(prompt);
	free(prompt);
	return (line);
}

void	error_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int	is_parent_needed(t_cmd *cmd)
{
	if (!cmd)
		return (0);
	if (cmd->builtin == BI_CD)
		return (1);
	if (cmd->builtin == BI_EXIT)
		return (1);
	if (cmd->builtin == BI_EXPORT)
		return (1);
	if (cmd->builtin == BI_UNSET)
		return (1);
	return (0);
}

int	is_builtin(t_cmd *cmd)
{
	if (cmd->builtin != BI_NONE)
		return (1);
	return (0);
}

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
