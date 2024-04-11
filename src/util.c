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
    char argvguest[4096];
    char *temp = argvguest;
    int val = 0;

    int arg_gc;
    int env_gc;
    int argv_bytes = 0;

    char *split;

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

    arg_gc = get_argc(argvguest);
    write_double_word(sp_addr, arg_gc);
    printf("Guest argc - %d\n", read_double_word(sp_addr));
    sp_addr += 8;

    env_gc = get_envp_count(envp);

    int total_offset_data = ((arg_gc + 1) + (env_gc + 1) + 4) * 8;
    printf("Total env vars - %d\n", env_gc);
    printf("Total offset to write bytes - %x\n", total_offset_data);

    char *argg[arg_gc];
    argg[0] = strdup(argv[argc - 2]);
    argv_bytes += strlen(argg[0]) + 1;
    printf("'%s' length is %d\n", argg[0], strlen(argg[0]) + 1);

    split = strtok(argvguest, " ");
    int numsplit = 1;
    while(split != NULL && numsplit != arg_gc)
    {
        printf("numsplit - %d | arg_gc - %d\n", numsplit, arg_gc);
        argg[numsplit] = strdup(split);
        argv_bytes += strlen(argg[numsplit]) + 1;
        printf("'%s' length is %d\n", argg[numsplit], strlen(argg[numsplit]) + 1);

        split = strtok(NULL, " ");
        numsplit++;
    }

    int envp_offset = (argv_bytes / 8) * 8;
    int envp_bc = get_envp_bytes_count(char** envp);

    printf("memory alignment %d\n", envp_offset);

    printf("Total bytes for argv - %d\n", argv_bytes);
    printf("Total bytes for envp - %d\n", envp_bc);



    uint8_t *arg_bytes = (uint8_t*) argg[1];

    for(int i = 0; i < argv_bytes; i++)
    {
        printf("%2x\n", arg_bytes[i]);
    }
}

char* get_argv_bytes(char** argv)
{

}

uint64_t get_argc(char* args)
{
    int total_args = 0;
    int running_total = strlen(args) + 1;
    printf("%s\n", args);
    printf("TEST\n");
    printf("%d\n", running_total);

    for(int i = 0; i < running_total; i++)
    {
        if(args[i] == ' ')
        {
            total_args++;
        }
    }

    // return total number of spaces in file + 1 for the first last arg + 1 for the executable itself -1 for space at end of file
    return total_args + 1;
}

int get_envp_count(char** envp)
{
    int i = 0;
    while(*envp)
    {
        i++;
    }
    return i;
}

int get_envp_bytes_count(char** envp)
{
    int i = 0;
    while(*envp)
    {
        i += strlen(*envp) + 1;
    }
    return i;
}

