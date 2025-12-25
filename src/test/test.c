#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// ./minishell echo |  wc -c
//       0       1  2  3  4
static  void  error_exit(const char *msg)
{
  perror(msg);
  exit(1);
}

int main(int argc, char **argv) 
{
  int pipe_fd[2];
  int pipe_control;
  char *args[] = {"/bin/echo", "hello", NULL};
  char *args2[] = {"/usr/bin/wc", "-c", NULL};
  pid_t pid1;
  pid_t pid2;

  if (pipe(pipe_fd) == -1)
    error_exit("fd failed");
  pid1 = fork();
  if (pid1 == -1)
    error_exit("fork failed");
  else if (pid1 == 0)
  {
    // child 1 || escrever (echo)
    if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
      error_exit("dup2 'stdout' failed");
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    write(3, "ola do filho", strlen("ola do filho"));
    execv(args[0], args);
    error_exit("execev(1) failed");
  }
  pid2 = fork();
  if (pid2 == -1)
    error_exit("fork failed");
  else if(pid2 == 0)
  {
    // child 2 || ler (wc)
    dup2(pipe_fd[0], STDIN_FILENO);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    execv(args2[0], args2);
    error_exit("execv(2) failed");
  }
  //close(pipe_fd[0]);
  close(pipe_fd[1]);
  
  waitpid(pid1, NULL, 0);
  waitpid(pid2, NULL, 0);
  return (0);
}