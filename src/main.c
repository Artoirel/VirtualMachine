#include <elf.h>
#include <stdio.h>
#include "error.h"
#include "elf_helper.h"
#include "address_type.h"
#include "data_type.h"
#include "memory.h"


int main(int argc, char *argv[]) {
    char *file;

    for(int i = 0; i < argc; i++)
    {
        file = argv[i];
    }

    printf("%s", file);
    
     write_double_word(1000012016, 0xdeadbeef);

     data_t test;
     test.data = read_double_word(1000012016);

    printf("0x%16x\n\n", test.data);

    printf("0x%08x\n", test.words.w1);
    printf("0x%08x\n\n", test.words.w2);

    printf("0x%04x\n", test.halfs.h1);
    printf("0x%04x\n", test.halfs.h2);
    printf("0x%04x\n", test.halfs.h3);
    printf("0x%04x\n\n", test.halfs.h4);

    printf("0x%02x\n", test.bytes.b1);
    printf("0x%02x\n", test.bytes.b2);
    printf("0x%02x\n", test.bytes.b3);
    printf("0x%02x\n", test.bytes.b4);
    printf("0x%02x\n", test.bytes.b5);
    printf("0x%02x\n", test.bytes.b6);
    printf("0x%02x\n", test.bytes.b7);
    printf("0x%02x\n\n", test.bytes.b8);


    if(argc < 2){
        THROW_ERROR("No file provided, please specify file");
    }

    Elf64_Ehdr* header = (Elf64_Ehdr*) create_hdr(argv[1]);
    Elf64_Shdr* sec = (Elf64_Shdr*) create_shdr(header);
    get_main(header, sec, argc - 1, &argv[1]);
    
    printf("Success!");
    return EXIT_SUCCESS;
}

