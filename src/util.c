#include "util.h"
#include "memory.h"
#include "register_file.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "error.h"
#include <unistd.h>



int running_total = 0;

void load_stack(int argc, char* argv[], char*envp[], uint64_t sp_addr)
{
    int fd = -1;
    char *argvguest;
    int arg_gc;
    uint64_t total_args = 2;
    int running_total = 0;
    char *temp = argvguest;
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

    argvguest = get_argv_string(fd);
    arg_gc = get_argc(argvguest);

    char *argg[total_args + 1];

    write_double_word(sp_addr, total_args);
    sp_addr += 8;

    argg[0] = strdup(argv[argc - 2]);
    total_argv_bytes += strlen(argg[0]);
    argg[total_args] = 0;

    split = strtok(argvguest, " ");
    int numsplit = 1;
    while(split != NULL)
    {
        argg[numsplit] = strdup(split);
        total_argv_bytes += strlen(argg[numsplit]) + 1;

        split = strtok(NULL, " ");
        running_total += strlen(argg[numsplit]) + 9;
        numsplit++;
    }

    uint8_t *arg_bytes = (uint8_t*) argg[1];

    printf("%d\n", total_args);

    for(int i = 0; i < total_argv_bytes; i++)
    {
        printf("%2x\n", arg_bytes[i]);
    }

    running_total += 40;

    while(*envp)
    {
        running_total += strlen(*envp) + 9;
        printf("envp - %s\n", *envp++);
    }
}

char* get_argv_string(int fd)
{
    char argvguest[4096];
    char *temp = argvguest;
    int val = 0;

    do
    {
        val = read(fd, temp++, 1);
    } while(val == 1);

    printf("Guest argc - %d\n", get_argc(argvguest));

    return argvguest;
}

uint64_t get_argc(char* args)
{
    int total_args = 0;
    int running_total = strlen(args) + 1;

    for(int i = 0; i < running_total; i++)
    {
        if(args[i] == ' ')
        {
            total_args++;
        }
    }

    // return total number of spaces in file + 1 for the first last arg + 1 for the executable itself
    return total_args + 2;
}

