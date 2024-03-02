#ifndef __ELF_HELPER_H__
#define __ELF_HELPER_H__

void* create_hdr(char* file);

void* create_shdr(void *header);

void get_main(void* header, void* sec, int argc, char* argv[]);

#endif
