# include "../includes/minishell.h"

char	*ft_readline(void)
{
	char	cwd[BUFSIZ];
	char	*prompt;
	char	*line;

	if (!getcwd(cwd, sizeof(cwd)))
		return (readline(" > "));

	prompt = ft_strjoin(cwd, " > ");
	line = readline(prompt);
	free(prompt);
	return (line);
}

static	void	error_exit(char *msg)
{
	perror("error: ");
	exit(1);
}

int	main(int argc, char **argv, char **env)
{
	t_cmd	*cmd;
	char *line;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		error_exit("malloc error\n");
	cmd ->args = malloc(sizeof(char*) * 2);
	cmd ->builtin = BI_NONE;
	cmd ->pid = 0;
	cmd ->redirs = NULL;
	cmd ->next = NULL; 
	
	while (1)
	{
		line = ft_readline();
		if (line == NULL)
			break;
		else
			add_history(line);
		free(line);
	}
}