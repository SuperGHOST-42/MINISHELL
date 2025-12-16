#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

static void perror_exit(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(void)
{
  int p[2];
  pid_t pid1;
  char *buf;
  int bytes_read;

  if (pipe(p) == -1)
    perror_exit("Pipe fail\n");
  
  pid1 = fork();
  if (pid1 == -1)
    perror_exit("Fork fail");
  
  if (pid1 == 0)
  {
    close(p[0]);
    dup2(p[1], 1);
    write (1, "ABC", 3);
    close (p[1]);
    exit(0);
  }
  close (p[1]);

  bytes_read = read(p[0], buf, 3);
  if (bytes_read > 0 )
  {
    buf[bytes_read] = '\0';
    write (1, buf, 3);
    close(p[0]);
  }
  waitpid(pid1, 0, 0);
  return (0);
}
