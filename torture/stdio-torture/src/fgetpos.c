#include <stdlib.h>
#include <stdio.h>

int main(){
    FILE *fd;
    fpos_t pos;

    fd = fopen("./temp","w");
    if (!fd)
        exit(1);

    if (fprintf(fd,"hello") != 5)
        exit(1);

    if (fseek(fd,2,SEEK_SET) != 0)
        exit(1);

    if (fgetpos(fd,&pos) != 0)
        exit(1);

    if (fclose(fd) != 0)
        exit(1);

    return 0;
}

