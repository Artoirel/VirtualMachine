#include "decode.h"
#include "memory.h"
#include "register_file.h"
#include <stdio.h>
#include <stdint.h>
#include "inst_type.h"

void decode_loop(uint64_t PC)
{
    uint64_t end = 0;
    while(end < 10000)
    {
        inst_t instruction;
        instruction.instruction = read_word(PC);
        printf("0x%.7b\n", instruction.encoding.opcode);

        PC += 4;
    }
}