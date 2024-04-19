#include "decode.h"
#include "memory.h"
#include "register_file.h"
#include <stdio.h>
#include <stdint.h>
#include "inst_type.h"
#include "rv64_opcodes.h"
#include <assert.h>

void decode_loop(uint64_t PC)
{
    while(PC)
    {
        inst_t instruction;
        instruction.instruction = read_word(PC);
        PC = dispatch(instruction, PC);
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
            pretty_print(instruction, PC);
            assert(0 && "RV64_OP_OP_IMM\n");
            return 0; //0x13    /* 0010011 */
        case RV64_OP_AUIPC:
            pretty_print(instruction, PC);
            //            printf("auipc  $r%d  0x%lx\n", instruction.u_type.rd, u_imm(instruction.u_type) << 12 + PC);
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
            write_reg_long(instruction.j_type.rd, PC + 4);
            return PC + j_imm(instruction.j_type);; //0x6f    /* 1101111 */
        case RV64_OP_SYSTEM:
            assert(0 && "RV64_OP_SYSTEM\n");
            return 0; //0x73    /* 1110011 */
        default: return 0;
    }
}

void pretty_print(inst_t instruction, uint64_t PC)
{
    printf("%8x:\t%8x\t", PC, instruction.instruction);
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
            printf("%8x\n", instruction.instruction);
            //printf("%8x:\t%8x\tjal\t%x\n", PC, instruction.instruction, PC + imm);
            return 0; //0x13    /* 0010011 */
        case RV64_OP_AUIPC:
            printf("auipc  $r%d  0x%lx\n", instruction.u_type.rd, u_imm(instruction.u_type) << 12 + PC);
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
            uint64_t imm = j_imm(instruction.j_type);
            printf("jal\t0x%x\n", PC + imm);
            return 0; //0x6f    /* 1101111 */
        case RV64_OP_SYSTEM:
            assert(0 && "RV64_OP_SYSTEM\n");
            return 0; //0x73    /* 1110011 */
        default: return 1;
    }
}

uint64_t j_imm(j_inst_t j)
{
    uint64_t val4 = 0;
    if(j.imm4 == 1)
    {
        val4 = 0xFFFFFFFF;
    }

    uint64_t val1 = j.imm1;
    uint64_t val2 = j.imm2 << 10;
    uint64_t val3 = j.imm3 << 11;
    val4 = val4 << 19;

    uint64_t val = (val1 | val2 | val3 | val4) << 1;
    return val;
}

uint64_t u_imm(u_inst_t u)
{
    uint64_t val = 0;
    if(u.sext == 1)
    {
        val = 0xFFFFFFFF;
    }

    val = (val << 20) | u.imm;

    return val;
}

