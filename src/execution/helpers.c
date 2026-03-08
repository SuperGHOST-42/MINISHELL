#include "../../includes/minishell.h"
#include "../../includes/minishell_parse.h"

char	*ft_readline(void)
{
	char	cwd[BUFSIZ];
	char	*prompt;
	char	*line;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		rl_already_prompted = 0;
		return (readline(" > "));
	}
	prompt = ft_strjoin(cwd, " > ");
	if (!prompt)
	{
		rl_already_prompted = 0;
		return (readline(" > "));
	}
	rl_already_prompted = 0;
	line = readline(prompt);
	free(prompt);
	return (line);
}

void	error_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	child_cleanup_exit(t_shell *shell, t_cmd *cmds, int status)
{
	if (cmds)
		free_cmds(cmds);
	if (shell)
	{
		free_env_exec(shell->env);
		free(shell);
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(status);
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
