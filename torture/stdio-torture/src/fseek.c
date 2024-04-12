#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
    FILE *fd;
    char wrbuff[] = "hello";
    char *rdbuff = calloc(6,1);

    fd = fopen("./temp","w");
    if (!fd)
        exit(1);

    if (fwrite(wrbuff,1,5,fd) != 5)
        exit(1);

    if (fseek(fd,0,SEEK_SET) != 0)
        exit(1);

    if (fwrite("t",1,1,fd) != 1)
        exit(1);

    if (fclose(fd) != 0)
        exit(1);

    fd = fopen("./temp","r");
    if (!fd)
        exit(1);

    if(fread(rdbuff,1,5,fd) != 5)
        exit(1);

    if (strcmp("tello",rdbuff) != 0)
        exit(1);
    
    return 0;
}

