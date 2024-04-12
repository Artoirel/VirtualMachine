#include <stdlib.h>
#include <stdio.h>

int main(){
    FILE *fd;
    char wrbuff[] = "hello";
    char *rdbuff = (char*) calloc(6,1);
    int count = 0;

    fd = fopen("./temp","w");
    if (!fd)
        exit(1);

    if (fprintf(fd,"%s",wrbuff) != 5)
        exit(1);

    if (fclose(fd) != 0)
        exit(1);

    fd = fopen("./temp","r");
    if (!fd)
        exit(1);

    while (!feof(fd)){
        if (fscanf(fd,"%s",rdbuff)!=1)
            exit(1);
        count++;
    }

    if (count != 1) exit(1);

    return 0;
}

