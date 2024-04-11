#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdint.h>


void load_stack(int argc, char* argv[], char*envp[], uint64_t sp_addr);

char* get_argv_string(int fd);

uint64_t get_argc(char* args);

int get_envp_count(char** envp);

int get_envp_bytes_count(char** envp);

#endif
