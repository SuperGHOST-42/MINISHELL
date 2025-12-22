#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <fcntl.h> 

int main(void)
{
	int  fd[2];
	int i;
	int fd_dup;
	char buf[4];
	ssize_t n;

	if (pipe(fd) == -1)
		return (1);

		

	while ((n = read(fd_dup, buf, sizeof(buf))) > 0)
	{
		write(1, buf, n);
		printf("\nn: %zi\n", n);
	}
	printf("\n n = %zi\n", n);
	/* aqui n == 0 => EOF */
	close(fd[0]);
	write(1, "\n", 1);
	return (0);
}
