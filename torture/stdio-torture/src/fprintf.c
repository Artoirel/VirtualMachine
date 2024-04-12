#include <stdlib.h>
#include <stdio.h>

int main(){
    FILE *fd;
    char wrbuff[] = "hello";
    char x = 'x';
    int y = 123;
    float z = 1.234;

    fd = fopen("./temp","w");
    if (!fd)
        exit(1);

    if (fprintf(fd,"%c %d %f\n%s",x,y,z,wrbuff) != 20)
        exit(1);

    if (fclose(fd) != 0)
        exit(1);

    return 0;
}

