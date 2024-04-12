#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
    FILE *fd;
    char wrbuff[] = "hello";
    char x = 'x';
    int y = 123;
    float z = 1.234;

    char *rdbuff = (char*)calloc(6,1);
    char a;
    int b;
    float c;

    fd = fopen("./temp","w");
    if (!fd)
        exit(1);

    if (fprintf(fd,"%c %d %f\n%s",x,y,z,wrbuff) != 20)
        exit(1);

    if (fclose(fd) != 0)
        exit(1);

    fd = fopen("./temp","r");
    if (!fd)
        exit(1);

    if (fscanf(fd,"%c",&a) != 1)
        exit(1);

    if (fscanf(fd,"%d%f",&b,&c) != 2)
        exit(1);

    if (fscanf(fd,"%s",rdbuff) != 1)
        exit(1);

    if (strcmp(wrbuff,rdbuff) != 0)
        exit(1);

    return 0;
}

