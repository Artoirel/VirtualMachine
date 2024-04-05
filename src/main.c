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
#include "util.h"

uint64_t PC = 0;

int main(int argc, char *argv[], char *envp[]) {
    init_rf(0x7ffffffff000);

    load_stack(argc, argv, envp, 0x7ffffffff000)

    printf("running total %d\n", running_total);

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

