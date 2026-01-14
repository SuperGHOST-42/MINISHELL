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