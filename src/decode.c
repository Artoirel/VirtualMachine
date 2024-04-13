#include "decode.h"
#include "memory.h"
#include "register_file.h"

decode(uint64_t PC)
{
    uint64_t end = 0;
    while(!end)
    {
        inst_t instruction;
        instruction.instruction = read_word(PC);
        printf("0x%8x\n", instruction.instruction);

        PC += 4;
    }
}