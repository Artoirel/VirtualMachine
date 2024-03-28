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

int main(int argc, char *argv[]) {
    if(argc < 2)
    {
        THROW_ERROR("No file provided, please specify file");
    }

    init_rf(0x7ffffffff000);

    rf_contents_t *fp_val = (rf_contents_t*) malloc(sizeof(rf_contents_t));
    fp_val->fpdouble = 6495;

    printf("PreWrite - FP: %f", fp_val->fpdouble);

    write_fp_reg(2, fp_val);

    rf_contents_t *val = (rf_contents_t*) malloc(sizeof(rf_contents_t));
    val->intdouble = 8858;

    write_reg(2,val);

    printf("FP Reg 2 : %f\n", read_fp_reg(2)->fpdouble);
    printf("Reg 2 : %d\n\n", read_reg(2)->intdouble);

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

