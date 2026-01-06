#include "../includes/minishell.h"
#include <readline/readline.h>

static void error_exit(const char *msg)
{
	perror(msg);
	exit(1);
}

char	*ft_getline(void)
{
	char cwd[BUFSIZ];
	char *buf;

	getcwd(cwd, sizeof(cwd));
	printf("%s", cwd);
	buf = readline(" $> ");
	return (buf);
}

int	main(int argc, char **argv, char **env)
{
	char *line;
	
	while (1)
	{
		line = ft_getline();
		if (line == NULL)
			break;
		printf("%s\n", line);
		// do stuff
		free(line);
	}
}
