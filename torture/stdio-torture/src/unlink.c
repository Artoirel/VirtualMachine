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

    if (unlink("./temp") != 0)
        exit(1);

    return 0;
}

