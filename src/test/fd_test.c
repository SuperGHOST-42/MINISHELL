#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

void  func(int *a)
{
   write(*a, "func", 4);
}

int main(void)
{
   int fd1;

   fd1 = open("note.txt", O_RDWR | O_APPEND);
   
   dup2(fd1, 1); //dup2(new_fd, old_fd);

   printf("Hello World\n"); // write in note.txt


}