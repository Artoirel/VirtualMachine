#include <elf.h>
#include <stdio.h>
#include "error.h"
#include "elf_helper.h"
#include "address_type.h"
#include "data_type.h"
#include "memory.h"
#include "register_file.h"
#include "rf_contents_type.h"

uint64_t PC = 0;

int main(int argc, char *argv[], char *envp[]) {
    if(argc < 2)
    {
        THROW_ERROR("No file provided, please specify file");
    }

    while(*envp)
        printf("size of - envp%d\n", sizeof(envp));
        printf("envp - %s\n",*envp++);

    init_rf(0x7ffffffff000);

    write_reg_int(10, argc - 1);

    printf("Read reg 10 - %d\n", read_reg_int(10));


    int valid = check_elf(argv[1]);

    if(valid != 64)
    {
        THROW_ERROR("Invalid architecture")
    }

    Elf64_Ehdr* header = (Elf64_Ehdr*) create_hdr(argv[1]);

    PC = header->e_entry;

    get_loadable_segment(header);

    printf("%8x\n", read_word(PC));

    //get_main(header, sec, argc - 1, &argv[1]);

    printf("Success!");
    return EXIT_SUCCESS;
}

