#include "../includes/minishell.h"

void	free_cmd(t_cmd *cmd)
{
	int i;

	i = 0;
	while (cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
	free(cmd);
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