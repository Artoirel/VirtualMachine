#include <elf.h>
#include <stdio.h>
#include "error.h"
#include "elf_helper.h"
#include "address_type.h"


int main(int argc, char *argv[]) {
    data_t test;
    test.data = 0xffeeccdd11665522;

    printf("0x%16x\n\n", test.data);

    printf("0x%08x\n", test.words[0]);
    printf("0x%08x\n\n", test.words[1]);

    printf("0x%04x\n", test.halfs[0]);
    printf("0x%04x\n", test.halfs[1]);
    printf("0x%04x\n", test.halfs[2]);
    printf("0x%04x\n\n", test.halfs[3]);

    printf("0x%02x\n", test.bytest[0]);
    printf("0x%02x\n", test.bytest[1]);
    printf("0x%02x\n", test.bytest[2]);
    printf("0x%02x\n", test.bytest[3]);
    printf("0x%02x\n", test.bytest[4]);
    printf("0x%02x\n", test.bytest[5]);
    printf("0x%02x\n", test.bytest[6]);
    printf("0x%02x\n\n", test.bytest[7]);


    if(argc < 2){
        THROW_ERROR("No file provided, please specify file");
    }

    Elf64_Ehdr* header = (Elf64_Ehdr*) create_hdr(argv[1]);
    Elf64_Shdr* sec = (Elf64_Shdr*) create_shdr(header);
    get_main(header, sec, argc - 1, &argv[1]);
    
    printf("Success!");
    return EXIT_SUCCESS;
}

