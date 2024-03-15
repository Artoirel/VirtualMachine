    #include <elf.h>
    #include <stdio.h>
    #include "error.h"
    #include "elf_helper.h"
    #include "address_type.h"
    #include "data_type.h"
    #include "memory.h"


int main(int argc, char *argv[]) {
    if(argc < 2)
    {
        THROW_ERROR("No file provided, please specify file");
    }

    char *file = argv[1];

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

    int valid = check_elf(argv[1]);

    if(valid != 64)
    {
        THROW_ERROR("Invalid architecture")
    }

    Elf64_Ehdr* header = (Elf64_Ehdr*) create_hdr(argv[1]);

    Elf64_Phdr* phdr = (Elf64_Phdr*) create_phdr(header);

    Elf64_Phdr* pt_load = (Elf64_Phdr*) get_loadable_segment(header, phdr, PT_LOAD);
    Elf64_Phdr* pt_tls = (Elf64_Phdr*) get_loadable_segment(header, phdr, PT_TLS);

    printf("PT_LOAD\n");
    printf("p_type: %d\n", pt_load->p_type);
    printf("p_offset: %d\n", pt_load->p_offset);
    printf("p_filesz: %d\n", pt_load->p_filesz);
    printf("p_memsz: %d\n", pt_load->p_memsz);
    printf("p_vaddr: %d\n\n", pt_load->p_vaddr);

    printf("PT_TLS\n");
    printf("p_type: %d\n", pt_tls->p_type);
    printf("p_offset: %d\n", pt_tls->p_offset);
    printf("p_filesz: %d\n", pt_tls->p_filesz);
    printf("p_memsz: %d\n", pt_tls->p_memsz);
    printf("p_vaddr: %d\n\n", pt_tls->p_vaddr);

    Elf64_Shdr* sec = (Elf64_Shdr*) create_shdr(header);
    //get_main(header, sec, argc - 1, &argv[1]);

    printf("Success!");
    return EXIT_SUCCESS;
}

