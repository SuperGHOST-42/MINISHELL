#include "../../includes/minishell.h"

static void	free_redirs(t_redirs *r)
{
	t_redirs	*next;

	while (r)
	{
		next = r->next;
		free(r->target);
		free(r);
		r = next;
	}
}

void	free_tcmd(t_cmd *cmd)
{
	t_cmd	*next;
	int		i;

	while (cmd)
	{
		next = cmd->next;
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
				free(cmd->args[i++]);
			free(cmd->args);
		}
		free_redirs(cmd->redirs);
		free(cmd);
		cmd = next;
	}
}

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

void error_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	print_args(t_cmd *cmd)
{
	int	i;

	if (!cmd || !cmd->args)
		return ;
	i = 0;
	while (cmd->args[i])
	{
		printf("%s\n", cmd->args[i]);
		i++;
	}
}

void	print_env_list(t_shell *shell)
{
	t_env	*cur;

	if (!shell)
		return ;
	cur = shell->env;
	while (cur)
	{
		if(cur->key)
			printf("%s", cur->key);
		if (cur->value)
			printf("=%s", cur->value);
		printf("\n");
		cur = cur->next;
	}
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
	if (cmd && cmd->builtin != BI_NONE)
		return (1);
	return (0);
}

void	ft_putstr(char *str)
{
	if (!str)
		return ;
	while (*str)
		write(1, str++, 1);
	write(1, "\n", 1);
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