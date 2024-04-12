#include <stdlib.h>
#include <stdio.h>

int main(){
    FILE *fd;

    fd = fopen("./temp","r");
    if (fd)
        exit(1);

    fd = fopen("./temp","w");
    if (!fd)
        exit(1);

    return 0;
}
