#include "../includes/minishell.h"

void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
	}
	// TODO: free redirs depois
	free(cmd);
}

char	*ft_readline(void)
{
	char	cwd[BUFSIZ];
	char	*prompt;
	char	*line;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		printf("error getcwd ");
		return (readline(" > "));
	}
	prompt = ft_strjoin(cwd, " > ");
	line = readline(prompt);
	free(prompt);
	return (line);
}

void error_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void print_args(t_cmd *cmd)
{
	for(int i = 0; cmd->args[i] != NULL; i++)
	{
		printf("%s\n", cmd->args[i]);
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
	else
		return (0);
}

void	ft_putstr(char *str)
{
	while (*str)
	{
		write(1, str++, 1);
	}
	write(1, "\n", 1);
}