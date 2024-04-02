#include <elf.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "error.h"
#include "elf_helper.h"
#include "address_type.h"
#include "data_type.h"
#include "memory.h"
#include "register_file.h"
#include "rf_contents_type.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

uint64_t PC = 0;

int main(int argc, char *argv[], char *envp[]) {
    if(argc < 2)
    {
        THROW_ERROR("No file provided, please specify file");
    }

    int argvFile = -1;

    if(argc > 2)
    {
        int i = 0;
        total_args++;
        argvFile = open(argv[argc - 1], O_RDONLY);
        char* temp = argvguest;
        do
        {
            val = read(argvFile, temp++, 1);
            i++;
        } while(val == 1);
    }

    running_total += strlen(argvguest) + 1;

    for(int i = 0; i < running_total; i++)
    {
        if(argvguest[i] == ' ')
        {
            total_args++;
        }
    }

    char *argg[total_args - 1];

    char *split;

    split = strtok(argvguest, " ");
    int numsplit = 0;
    while(split != NULL)
    {
        argg[numsplit] = strdup(split);
        printf("%s\n", argg[numsplit]);

        split = strtok(NULL, " ");
        running_total += strlen(argg[numsplit]) + 9;
	    numsplit++;
    }

    running_total += 40;

    while(*envp)
    {
        running_total += strlen(*envp) + 9;
        printf("envp - %s\n", *envp++);
    }

    printf("running total %d\n", running_total);

    init_rf(0x7ffffffff000);

    //write_double_word(read_reg_long(2));

    write_reg_int(10, argc - 1);

    print_reg(10);

    int valid = check_elf(argv[1]);

    if(valid != 64)
    {
        THROW_ERROR("Invalid architecture")
    }

    Elf64_Ehdr* header = (Elf64_Ehdr*) create_hdr(argv[1]);

    PC = header->e_entry;

    get_loadable_segment(header);

    printf("Read reg 10 - %d\n", read_reg_int(10));

    printf("%8x\n", read_word(PC));

    printf("Success!");

    printf("%.16lx\n", read_word(PC));
    return EXIT_SUCCESS;
}

