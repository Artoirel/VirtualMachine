#include <stdlib.h>
#include <stdio.h>

int main(){
    FILE *fd;

    fd = fopen("./temp","w");
    if (!fd)
        exit(1);

    if (fputc('x',fd) != 'x')
        exit(1);

    if (fclose(fd) != 0)
        exit(1);

    return 0;
}
