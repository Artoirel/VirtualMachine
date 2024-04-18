#include "decode.h"
#include "memory.h"
#include "register_file.h"
#include <stdio.h>
#include <stdint.h>
#include "inst_type.h"
#include "rv64_opcodes.h"
#include <assert.h>

uint64_t PC_g = 0;

void decode_loop(uint64_t PC)
{
    PC;
    uint64_t end = 0;
    while(!end)
    {
        inst_t instruction;
        instruction.instruction = read_word(PC);
        end = dispatch(instruction, PC);
        PC += 4;
    }
}

int dispatch(inst_t instruction, uint64_t PC)
{
    switch(instruction.encoding.opcode)
    {
        case RV64_OP_LOAD:
            assert(0 && "LOAD");
            return 0; //0x03    /* 0000011 */
        case RV64_OP_LOAD_FP:
            assert(0 && "LOAD FP");
            return 0; //0x07    /* 0000111 */
        case RV64_OP_MISC_MEM:
            assert(0 && "RV64_OP_MISC_MEM\n");
            return 0; //0x0f    /* 0001111 */
        case RV64_OP_OP_IMM:
            assert(0 && "RV64_OP_OP_IMM\n");
            return 0; //0x13    /* 0010011 */
        case RV64_OP_AUIPC:
            assert(0 && "RV64_OP_AUIPC\n");
            return 0; //0x17    /* 0010111 */
        case RV64_OP_OP_IMM32:
            assert(0 && "RV64_OP_OP_IMM32\n");
            return 0; //0x1b    /* 0011011 */
        case RV64_OP_STORE:
            assert(0 && "RV64_OP_STORE\n");
            return 0; //0x23    /* 0100011 */
        case RV64_OP_STORE_FP:
            assert(0 && "RV64_OP_STORE_FP\n");
            return 0; //0x27    /* 0100111 */
        case RV64_OP_AMO:
            assert(0 && "RV64_OP_AMO\n");
            return 0; //0x2f    /* 0101111 */
        case RV64_OP_OP:
            assert(0 && "RV64_OP_OP\n");
            return 0; //0x33    /* 0110011 */
        case RV64_OP_LUI:
            assert(0 && "RV64_OP_LUI\n");
            return 0; //0x37    /* 0110111 */
        case RV64_OP_OP32:
            assert(0 && "RV64_OP_OP32\n");
            return 0; //0x3b    /* 0111011 */
        case RV64_OP_MADD:
            assert(0 && "RV64_OP_MADD\n");
            return 0; //0x43    /* 1000011 */
        case RV64_OP_MSUB:
            assert(0 && "RV64_OP_MSUB\n");
            return 0; //0x47    /* 1000111 */
        case RV64_OP_NMSUB:
            assert(0 && "RV64_OP_NMSUB\n");
            return 0; //0x4b    /* 1001011 */
        case RV64_OP_NMADD:
            assert(0 && "RV64_OP_NMADD\n");
            return 0; //0x4f    /* 1001111 */
        case RV64_OP_FP:
            assert(0 && "RV64_OP_FP\n");
            return 0; //0x53    /* 1010011 */
        case RV64_OP_BRANCH:
            assert(0 && "RV64_OP_BRANCH\n");
            return 0; //0x63    /* 1100011 */
        case RV64_OP_JALR:
            assert(0 && "RV64_OP_JALR\n");
            return 0; //0x67    /* 1100111 */
        case RV64_OP_JAL:
            pretty_print(instruction, PC);
            //assert(0 && "RV64_OP_JAL\n");
            return 0; //0x6f    /* 1101111 */
        case RV64_OP_SYSTEM:
            assert(0 && "RV64_OP_SYSTEM\n");
            return 0; //0x73    /* 1110011 */
        default: return 1;
    }
}

void pretty_print(inst_t instruction, uint64_t PC)
{
    printf("%d\n", PC);
    switch(instruction.encoding.opcode)
    {
        case RV64_OP_LOAD:
            return 0; //0x03    /* 0000011 */
        case RV64_OP_LOAD_FP:
            assert(0 && "RV64_OP_LOAD_FP\n");
            return 0; //0x07    /* 0000111 */
        case RV64_OP_MISC_MEM:
            assert(0 && "RV64_OP_MISC_MEM\n");
            return 0; //0x0f    /* 0001111 */
        case RV64_OP_OP_IMM:
            assert(0 && "RV64_OP_OP_IMM\n");
            return 0; //0x13    /* 0010011 */
        case RV64_OP_AUIPC:
            assert(0 && "RV64_OP_AUIPC\n");
            return 0; //0x17    /* 0010111 */
        case RV64_OP_OP_IMM32:
            assert(0 && "RV64_OP_OP_IMM32\n");
            return 0; //0x1b    /* 0011011 */
        case RV64_OP_STORE:
            assert(0 && "RV64_OP_STORE\n");
            return 0; //0x23    /* 0100011 */
        case RV64_OP_STORE_FP:
            assert(0 && "RV64_OP_STORE_FP\n");
            return 0; //0x27    /* 0100111 */
        case RV64_OP_AMO:
            assert(0 && "RV64_OP_AMO\n");
            return 0; //0x2f    /* 0101111 */
        case RV64_OP_OP:
            assert(0 && "RV64_OP_OP\n");
            return 0; //0x33    /* 0110011 */
        case RV64_OP_LUI:
            assert(0 && "RV64_OP_LUI\n");
            return 0; //0x37    /* 0110111 */
        case RV64_OP_OP32:
            assert(0 && "RV64_OP_OP32\n");
            return 0; //0x3b    /* 0111011 */
        case RV64_OP_MADD:
            assert(0 && "RV64_OP_MADD\n");
            return 0; //0x43    /* 1000011 */
        case RV64_OP_MSUB:
            assert(0 && "RV64_OP_MSUB\n");
            return 0; //0x47    /* 1000111 */
        case RV64_OP_NMSUB:
            assert(0 && "RV64_OP_NMSUB\n");
            return 0; //0x4b    /* 1001011 */
        case RV64_OP_NMADD:
            assert(0 && "RV64_OP_NMADD\n");
            return 0; //0x4f    /* 1001111 */
        case RV64_OP_FP:
            assert(0 && "RV64_OP_FP\n");
            return 0; //0x53    /* 1010011 */
        case RV64_OP_BRANCH:
            assert(0 && "RV64_OP_BRANCH\n");
            return 0; //0x63    /* 1100011 */
        case RV64_OP_JALR:
            assert(0 && "RV64_OP_JALR\n");
            return 0; //0x67    /* 1100111 */
        case RV64_OP_JAL:
            printf("%8x:\t%8x\tjal\t%8x", PC, instruction.instruction, PC + 4 + j_imm(instruction.j_type));
            return 0; //0x6f    /* 1101111 */
        case RV64_OP_SYSTEM:
            assert(0 && "RV64_OP_SYSTEM\n");
            return 0; //0x73    /* 1110011 */
        default: return 1;
    }
}

uint32_t j_imm(j_inst_t j)
{
    uint32_t val1 = j.imm1 << 1;
    uint32_t val2 = j.imm2 << 11;
    uint32_t val3 = j.imm3 << 19;
    uint32_t val4 = j.imm4 << 20;
    return val1 | val2 | val3 | val4;
}
