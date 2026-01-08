#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main(void)
{
	pid_t pid;
	
	//pid = fork();

	if (fork() == 0)
	{
		char *argv[] = {"/bin/echo", "Hello", "World", NULL};
		execv(argv[0], argv);
		perror("Failed");
	}

	printf("test");




	return (0);
} 