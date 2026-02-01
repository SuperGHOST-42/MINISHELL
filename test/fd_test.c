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
   int fdp[2];
   long 
   int fd1 = open("note.txt", O_RDWR);
   int fd2 = open("note.txt", O_RDWR);
   char c;

   read(fd1, &c, 1);
   write(1, &c, 1);
   read(fd1, &c, 1);
   write(1, &c, 1);
   read(fd2, &c, 1);
   write(1, &c, 1);

   return (0);
}