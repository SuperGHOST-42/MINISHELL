#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

static void	fatal(const char *msg)
{
	perror(msg);
	exit(1);
}

int	main(void)
{
	int		fd_p[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd_p) == -1)
		fatal("pipe");

	pid1 = fork(); // 265423
    printf("%d\n", pid1);
	if (pid1 == -1)
		fatal("fork");

	if (pid1 == 0)
	{
		/* CHILD 1: echo ola  -> escreve para o pipe */
		if (dup2(fd_p[1], STDOUT_FILENO) == -1)
			fatal("dup2 child1");
		close(fd_p[0]);
		close(fd_p[1]);
		char *argv[] = {"echo", "ola", NULL};
		execvp(argv[0], argv);
		fatal("execvp echo");
	}
	pid2 = fork();
	if (pid2 == -1)
		fatal("fork");
	if (pid2 == 0)
	{
		/* CHILD 2: wc -c  -> lê do pipe */
		if (dup2(fd_p[0], STDIN_FILENO) == -1)
			fatal("dup2 child2");
		close(fd_p[0]);
		close(fd_p[1]);
		char *argv[] = {"wc", "-c", NULL};
		execvp(argv[0], argv);
		fatal("execvp wc");
	}
	/* PARENT: não usa o pipe, então fecha tudo */
	close(fd_p[0]);
	close(fd_p[1]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
