#include "util.h"
#include "memory.h"
#include "register_file.h"
#include <stdio.h>

int running_total = 0;

void load_stack(int argc, char* argv[], char*envp[], uint64_t sp_addr)
{
    int fd = -1;
    uint8_t argvguest[4096];
    int val = 0;
    uint64_t total_args = 1;
    int running_total = 0;
    char *temp = argvguest;
    char *argg[total_args + 1];
    char *split;
    int total_argv_bytes = 0;

    if(argc < 2)
    {
        THROW_ERROR("No file provided, please specify file");
    }

    if(argc > 2)
    {
        fd = open(argv[argc - 1], O_RDONLY);
    }

    do
    {
        val = read(fd, temp++, 1);
    } while(val == 1);

    running_total += strlen(argvguest) + 1;

    for(int i = 0; i < running_total; i++)
    {
        if(argvguest[i] == ' ')
        {
            total_args++;
        }
    }

    write_double_word(sp_addr, total_args);
    sp_addr += 8;

    argg[0] = argv[argc - 2];
    total_argv_bytes += strlen(argg[0]);
    argg[total_args] = 0;

    split = strtok(argvguest, " ");
    int numsplit = 1;
    while(split != NULL)
    {
        argg[numsplit] = strdup(split);
        total_argv_bytes += strlen(argg[numsplit]) + 1;
        printf("%s\n", argg[numsplit]);

        split = strtok(NULL, " ");
        running_total += strlen(argg[numsplit]) + 9;
        numsplit++;
    }

    uint8_t *arg_bytes = (uint8_t*) argg[0];

    for(int i = 0; i < total_argv_bytes; i++)
    {
        printf("%.2x\n", arg_bytes[i]);
    }

    running_total += 40;

    while(*envp)
    {
        running_total += strlen(*envp) + 9;
        printf("envp - %s\n", *envp++);
    }
}

uint8_t get_argc(int fd)
{

}

