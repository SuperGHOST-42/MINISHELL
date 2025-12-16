#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

static void fatal(const char *msg)
{
    perror(msg);
    exit(1);
}
int	main(void)
{
	int		fd_p[2];
	pid_t 	pid1;
	pid_t 	pid2;
	

	pipe(fd_p);
	pid1 = fork();

	if (pid1 == 0)
	{
		dup2(fd_p[1], 1);
		write(1, "abc", 3);
		char line[4];
		read(fd_p[0], line, 3);
		printf("line: %s\n", line);
	}


}