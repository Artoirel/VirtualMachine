#include "util.h"
#include "memory.h"
#include "register_file.h"

int running_total = 0;

void load_stack(int fd, char*envp[], uint64_t sp_addr)
{
    uint8_t argvguest[4096];
    int val = 0;
    int total_args = 1;
}

