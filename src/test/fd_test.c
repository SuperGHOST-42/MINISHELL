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
   int fd = open("note.txt", O_RDONLY);

}