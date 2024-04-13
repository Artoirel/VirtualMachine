#include "decode.h"
#include "memory.h"
#include "register_file.h"
#include <stdio.h>
#include <stdint.h>
#include "inst_type.h"
#include "rv64_opcodes.h"

void decode_loop(uint64_t PC)
{
    uint64_t end = 0;
    while(!end)
    {
        inst_t instruction;
        instruction.instruction = read_word(PC);
        end = dispatch(instruction);
        PC += 4;
    }
}

int dispatch(inst_t instruction)
{
    switch(instruction.encoding.opcode)
    {
        case RV64_OP_LOAD:
            printf("RV64_OP_LOAD\n");
            return 0;
        case RV64_OP_LOAD_FP:
            printf("RV64_OP_LOAD_FP\n");
            return 0; //0x07    /* 0000111 */
        case RV64_OP_MISC_MEM:
            printf("RV64_OP_MISC_MEM\n");
            return 0; //0x0f    /* 0001111 */
        case RV64_OP_OP_IMM:
            printf("RV64_OP_OP_IMM\n");
            return 0; //0x13    /* 0010011 */
        case RV64_OP_AUIPC:
            printf("RV64_OP_AUIPC\n");
            return 0; //0x17    /* 0010111 */
        case RV64_OP_OP_IMM32:
            printf("RV64_OP_OP_IMM32\n");
            return 0; //0x1b    /* 0011011 */
        case RV64_OP_STORE:
            printf("RV64_OP_STORE\n");
            return 0; //0x23    /* 0100011 */
        case RV64_OP_STORE_FP:
            printf("RV64_OP_STORE_FP\n");
            return 0; //0x27    /* 0100111 */
        case RV64_OP_AMO:
            printf("RV64_OP_AMO\n");
            return 0; //0x2f    /* 0101111 */
        case RV64_OP_OP:
            printf("RV64_OP_OP\n");
            return 0; //0x33    /* 0110011 */
        case RV64_OP_LUI:
            printf("RV64_OP_LUI\n");
            return 0; //0x37    /* 0110111 */
        case RV64_OP_OP32:
            printf("RV64_OP_OP32\n");
            return 0; //0x3b    /* 0111011 */
        case RV64_OP_MADD:
            printf("RV64_OP_MADD\n");
            return 0; //0x43    /* 1000011 */
        case RV64_OP_MSUB:
            printf("RV64_OP_MSUB\n");
            return 0; //0x47    /* 1000111 */
        case RV64_OP_NMSUB:
            printf("RV64_OP_NMSUB\n");
            return 0; //0x4b    /* 1001011 */
        case RV64_OP_NMADD:
            printf("RV64_OP_NMADD\n");
            return 0; //0x4f    /* 1001111 */
        case RV64_OP_FP:
            printf("RV64_OP_FP\n");
            return 0; //0x53    /* 1010011 */
        case RV64_OP_BRANCH:
            printf("RV64_OP_BRANCH\n");
            return 0; //0x63    /* 1100011 */
        case RV64_OP_JALR:
            printf("RV64_OP_JALR\n");
            return 0; //0x67    /* 1100111 */
        case RV64_OP_JAL:
            printf("RV64_OP_JAL\n");
            return 0; //0x6f    /* 1101111 */
        case RV64_OP_SYSTEM:
            printf("RV64_OP_SYSTEM\n");
            return 0; //0x73    /* 1110011 */
        default: return 1;
    }
}