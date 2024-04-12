#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
    FILE *fd;
    char wrbuff[] = "hello";
    char *rdbuff = (char*) calloc(6,1);

    fd = fopen("./foo","w");
    if (!fd)
        exit(1);

    if (fwrite(wrbuff,1,5,fd) != 5)
        exit(1);

    if (fclose(fd) != 0)
        exit(1);

    if (rename("./foo","./temp") != 0)
        exit(1);

    fd = fopen("./temp","r");
    if (!fd)
        exit(1);

    if(fread(rdbuff,1,5,fd) != 5)
        exit(1);

    if (strcmp(wrbuff,rdbuff) != 0)
        exit(1);
    
    return 0;
}

