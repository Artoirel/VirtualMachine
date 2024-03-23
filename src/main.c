#include <elf.h>
#include <stdio.h>
#include "error.h"
#include "elf_helper.h"
#include "address_type.h"
#include "data_type.h"
#include "memory.h"
#include "register_file.h"
#include "rf_contents_type.h"

int main(int argc, char *argv[]) {
    if(argc < 2)
    {
        THROW_ERROR("No file provided, please specify file");
    }

    init_rf(0, 0);

    rf_contents_t fp_val;
    fp_val.fpdouble = 6495;

    printf("PreWrite - FP: %f", fp_val.fpdouble);

    write_fp_reg(2, fp_val);

    rf_contents_t val;
    val.intdouble = 8858;

    write_reg(2,val);

    printf("FP Reg 2 : %f\n", read_fp_reg(2).fpdouble);
    printf("Reg 2 : %d\n\n", read_reg(2).intdouble);

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

    get_loadable_segment(header);

    //get_main(header, sec, argc - 1, &argv[1]);

    printf("Success!");
    return EXIT_SUCCESS;
}

