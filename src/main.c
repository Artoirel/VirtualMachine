#include <elf.h>
#include <stdio.h>
#include "error.h"
#include "elf_helper.h"
#include "address_type.h"


int main(int argc, char *argv[]) {
    address_t test;
    test.address = 4;

    printf("%x", test.L1);

    if(argc < 2){
        THROW_ERROR("No file provided, please specify file");
    }

    Elf64_Ehdr* header = (Elf64_Ehdr*) create_hdr(argv[1]);
    Elf64_Shdr* sec = (Elf64_Shdr*) create_shdr(header);
    get_main(header, sec, argc - 1, &argv[1]);
    
    printf("Success!");
    return EXIT_SUCCESS;
}

