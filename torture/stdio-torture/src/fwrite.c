#include <stdlib.h>
#include <stdio.h>

int main(){
    FILE *fd;
    char buff[] = "hello";

    fd = fopen("./temp","w");
    if (!fd)
        exit(1);

    if (fwrite(buff,1,5,fd) != 5)
        exit(1);

    if (fclose(fd) != 0)
        exit(1);

    return 0;
}

