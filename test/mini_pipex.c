#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

static void	error_exit(const char *msg)
{
	perror(msg);
	exit(1);
}
 
int	main(int argc, char **argv, char **env)
{
	int		fd_p[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd_p) == -1)
		error_exit("pipe");

	pid1 = fork();
	if (pid1 == -1)
		error_exit("fork");

	if (pid1 == 0)
	{
		// Child 1
		if (dup2(fd_p[1], STDOUT_FILENO) == -1)
			error_exit("dup2 child1");
		close(fd_p[0]);
		close(fd_p[1]);
		char *args[] = {"/bin/echo", "hello", NULL};
		execve(args[0], args, env);
		error_exit("execv child 1");
	}
	pid2 = fork();
	if (pid2 == -1)
		error_exit("fork");
	if (pid2 == 0)
	{
		// Child 2
		if (dup2(fd_p[0], STDIN_FILENO) == -1)
			error_exit("dup2 child2");
		close(fd_p[0]);
		close(fd_p[1]);
		char *args[] = {"/usr/bin/wc", "-c", NULL};
		execve(args[0], args, env);
		error_exit("execv child 2");
	}

	close(fd_p[0]);
	close(fd_p[1]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	for (int i = 0; env[i] != NULL; i++)
	{
		printf("%s\n", env[i]);
	}
	return (0);
}
