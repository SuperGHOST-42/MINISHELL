#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int p[2];
    char buf[10] = {0};

    pipe(p); 
    dup2(p[1], 1);

    write(1, "ABC", 3); // mete "ABC" no pipe (no kernel)

    read(p[0], buf, 3);    // tira 3 bytes do pipe para buf

    //write(1, buf, 3); 
    printf("%s\n", buf);     // escreve no terminal (stdout)
    //write(1, "\n", 1);

    close(p[0]);
    close(p[1]);
}

