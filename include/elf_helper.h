#ifndef __ELF_HELPER_H__
#define __ELF_HELPER_H__

#include <stdint.h>

int check_elf(char* file);

void* create_hdr(char* file);

void* create_phdr(void* header);

void get_loadable_segment(void* header);

void* create_shdr(void *header);

void get_main(void* header, void* sec, int argc, char* argv[]);

#endif
