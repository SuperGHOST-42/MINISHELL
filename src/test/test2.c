#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

static void	error_exit(const char *msg)
{
	perror(msg);
	exit(1);
}

int ft_strlen(char *str)
{
	int len = 0;
	while (str[len])
		len++;
	return (len);
}

void strrev(char *str)
{
	int i = strlen(str);
	i--;
	
	printf("i = %i\n", i);
	while (i >= 0)
	{
		write(4, &str[i], 1);
		i--;
	}
}
 
int	main(void) //./a.out echo ola | wc -c 
{
	int		fd, fd2;
	char 	*buf = malloc(100);
	pid_t	pid1;
	pid_t	pid2;

	fd = open("note.txt", O_RDWR);
	fd2 = open("file.txt", O_RDWR);

	int count = 1;
	while (count > 0)
	{
		count = read(fd, buf, 5);
		printf("read = %i\n", count);
		if(count == 0)
			break;
		buf[count] = '\0';
	}
	strrev(buf);
	free(buf);
	
	return (0);
}
