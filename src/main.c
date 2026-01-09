#include "../includes/minishell.h"
#include <string.h>

static	void error_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

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

static void print_args(t_cmd *cmd)
{
	for(int i = 0; cmd->args[i] != NULL; i++)
	{
		printf("%s\n", cmd->args[i]);
	}
}
char	*ft_readline(void)
{
	char	cwd[BUFSIZ];
	char	*prompt;
	char	*line;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		printf("error getcwd\n");
		return (readline(" > "));
	}
	prompt = ft_strjoin(cwd, " > ");
	line = readline(prompt);
	free(prompt);
	return (line);
}
void	parser(t_cmd *cmd)
{
	cmd->args = malloc(sizeof(char *) * 3);
	if(cmd->args == NULL)
		error_exit("Malloc failed");
	cmd->args[0] = ft_strdup("/bin/echo");
	cmd->args[1] = ft_strdup("Hello World");
	cmd->args[2] = NULL;
	cmd->builtin = 1;
	cmd->pid = -1;
	cmd->redirs = NULL;
	cmd->next = NULL;
}

int	is_parent_builtin(t_builtin bi)
{
	if (bi == BI_CD || bi == BI_UNSET ||bi == BI_EXIT || bi == BI_EXPORT)
		return (1);
	return (0);
}
int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	t_cmd	*cmd;
	char *line;
	pid_t pid;
	
	while (1)
	{
		line = ft_readline();
		if (line == NULL)
			break;
		else
			add_history(line);
		free(line);
		cmd = malloc(sizeof(t_cmd));
		////////////////////////////
		parser(cmd); // hugo
		////////////////////////////
		if (cmd->builtin != BI_NONE && is_parent_builtin(cmd->builtin))
		{
			TODO:
			exec_builtin(cmd);
		}
		else
		{
			pid = fork();
			if (pid == 0)
			{
				if (cmd->builtin != BI_NONE)
				{
					exec_builtin(cmd);
				}
				else
				{	
					TODO: 
					exec_all();
				}
			}
		}
	}
	perror("");
	return (EXIT_SUCCESS);
}