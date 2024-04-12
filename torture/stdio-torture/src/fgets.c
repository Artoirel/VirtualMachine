#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
    FILE *fd;
    char *buff = (char*)calloc(6,1);
    char *chk;

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

    chk = fgets(buff,6,fd);
    if (chk != buff)
        exit(1);

    if (strcmp(buff,"hello") != 0)
        exit(1);

    if (fclose(fd) != 0)
        exit(1);

    return 0;
}
