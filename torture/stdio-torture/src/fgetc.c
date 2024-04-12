#include <stdlib.h>
#include <stdio.h>

int main(){
    FILE *fd;

    fd = fopen("./temp","w");
    if (!fd)
        exit(1);

    if (fprintf(fd,"hello") != 5)
        exit(1);

    if (fclose(fd) != 0)
        exit(1);

    fd = fopen("./temp","r");
    if (!fd)
        exit(1);

    if (fgetc(fd) != 'h')
        exit(1);

    if (fclose(fd) != 0)
        exit(1);

    return 0;
}

