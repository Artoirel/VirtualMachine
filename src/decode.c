#include "decode.h"
#include "memory.h"
#include "register_file.h"
#include <stdio.h>
#include <stdint.h>
#include "inst_type.h"
#include "rv64_opcodes.h"
#include <assert.h>

int inst_count = 0;

void decode_loop(uint64_t PC)
{
    while(PC)
    {
        inst_t instruction;
        instruction.instruction = read_word(PC);
        PC = dispatch(instruction, PC);
        inst_count++;
    }
}

int dispatch(inst_t instruction, uint64_t PC)
{
    pretty_print(instruction, PC);
    switch(instruction.encoding.opcode)
    {
        case RV64_OP_LOAD:
            switch (instruction.i_type.funct3) {
                case RV64_FUNCT3_LB  :
                    assert(0 && "RV64_OP_LOAD - LB\n");
                    return; //0x0
                case RV64_FUNCT3_LH  :
                    assert(0 && "RV64_OP_LOAD - LH\n");
                    return; //0x1
                case RV64_FUNCT3_LW  :
                    assert(0 && "RV64_OP_LOAD - LW\n");
                    return; //0x2
                case RV64_FUNCT3_LBU :
                    assert(0 && "RV64_OP_LOAD - LBU\n");
                    return; //0x4
                case RV64_FUNCT3_LHU :
                    assert(0 && "RV64_OP_LOAD - LHU\n");
                    return; //0x5
                case RV64_FUNCT3_LWU :
                    assert(0 && "RV64_OP_LOAD - LWU\n");
                    return; //0x6

                case RV64_FUNCT3_LD  :
                    write_reg_long(instruction.i_type.rd, read_double_word(read_reg_long(instruction.i_type.rs1)) + i_imm(instruction.i_type));
                    return PC + 4; //0x3

            }
            return 0; //0x03    /* 0000011 */

        case RV64_OP_LOAD_FP:
            assert(0 && "LOAD FP");
            return 0; //0x07    /* 0000111 */
        case RV64_OP_MISC_MEM:
            assert(0 && "RV64_OP_MISC_MEM\n");
            return 0; //0x0f    /* 0001111 */

        case RV64_OP_OP_IMM:
            switch(instruction.i_type.funct3) {
                case RV64_FUNCT3_ADDI :
                    write_reg_long(instruction.i_type.rd,
                                   read_reg_long(instruction.i_type.rs1) + i_imm(instruction.i_type));
                    return PC + 4;// 0x0

                case RV64_FUNCT3_SLTI :
                    assert(0 && "RV64_OP_OP_IMM - SLTI\n");
                    return;// 0x2
                case RV64_FUNCT3_SLTIU:
                    assert(0 && "RV64_OP_OP_IMM - SLTIU\n");
                    return;// 0x3
                case RV64_FUNCT3_XORI :
                    assert(0 && "RV64_OP_OP_IMM - XORI\n");
                    return;// 0x4
                case RV64_FUNCT3_ORI  :
                    assert(0 && "RV64_OP_OP_IMM - ORI\n");
                    return;// 0x6

                case RV64_FUNCT3_ANDI :
                    write_reg_long(instruction.i_type.rd,
                                   read_reg_long(instruction.i_type.rs1) & i_imm(instruction.i_type));
                    return PC + 4;// 0x7

                case RV64_FUNCT3_SLLI :
                    write_reg_long(instruction.is_type.rd, read_reg_long(instruction.is_type.rs1) << is_imm_64(instruction.is_type));
                    return PC + 4;
                case RV64_FUNCT3_SRLI :
                    assert(0 && "RV64_OP_OP_IMM - SRLI\n");
                    return; //0x5
            }
            assert(0 && "UNKNOWN IMM INST");
            return 0; //0x13    /* 0010011 */

        case RV64_OP_AUIPC:
            write_reg_long(instruction.u_type.rd, (u_imm(instruction.u_type) << 12) + PC);
            return PC + 4; //0x17    /* 0010111 */

        case RV64_OP_OP_IMM32:
            assert(0 && "RV64_OP_OP_IMM32\n");
            return 0; //0x1b    /* 0011011 */

        case RV64_OP_STORE:
            switch (instruction.s_type.funct3) {
                case RV64_FUNCT3_SB :
                    assert(0 && "RV64_OP_STORE - SB\n");
                    return; //0x0
                case RV64_FUNCT3_SH :
                    assert(0 && "RV64_OP_STORE - SH\n");
                    return; //0x1
                case RV64_FUNCT3_SW :
                    assert(0 && "RV64_OP_STORE - SW\n");
                    return; //0x2
                case RV64_FUNCT3_SD:
                    write_double_word(read_reg_long(instruction.s_type.rs1) + s_imm(instruction.s_type), read_reg_long(instruction.s_type.rs2));
                    return PC + 4; //0x3
            }
            assert(0 && "RV64_OP_STORE\n");
            return 0; //0x23    /* 0100011 */

        case RV64_OP_STORE_FP:
            assert(0 && "RV64_OP_STORE_FP\n");
            return 0; //0x27    /* 0100111 */

        case RV64_OP_AMO:
            assert(0 && "RV64_OP_AMO\n");
            return 0; //0x2f    /* 0101111 */

        case RV64_OP_OP:

            switch(instruction.r_type.funct3)
            {

                case RV64_FUNCT3_ADD   :
                    switch(instruction.r_type.funct7)
                    {
                        case RV64_FUNCT7_ADD :
                            write_reg_long(instruction.r_type.rd, read_reg_long(instruction.r_type.rs1) + read_reg_long(instruction.r_type.rs2));
                            return PC + 4; //0x00
                        case RV64_FUNCT7_SUB :
                            assert(0 && "RV64_OP_OP - SUB\n");
                            return PC + 4; //0x20
                    }

                case RV64_FUNCT3_SLL   :
                    assert(0 && "RV64_OP_OP - SLL\n");
                    return PC + 4; // 0x1
                case RV64_FUNCT3_SLT   :
                    assert(0 && "RV64_OP_OP - SLT\n");
                    return PC + 4; // 0x2
                case RV64_FUNCT3_SLTU  :
                    assert(0 && "RV64_OP_OP - SLTU\n");
                    return PC + 4; // 0x3
                case RV64_FUNCT3_XOR   :
                    assert(0 && "RV64_OP_OP - XOR\n");
                    return PC + 4; // 0x4
                case RV64_FUNCT3_SRL   :
                    assert(0 && "RV64_OP_OP - SRL\n");
                    return PC + 4; // 0x5
                case RV64_FUNCT3_OR    :
                    assert(0 && "RV64_OP_OP - OR\n");
                    return PC + 4; // 0x6
                case RV64_FUNCT3_AND   :
                    assert(0 && "RV64_OP_OP - AND\n");
                    return PC + 4; // 0x7

            }
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
            switch(instruction.b_type.funct3)
            {
                case RV64_FUNCT3_BEQ  :
                    assert(0 && "RV64_OP_BRANCH - BEQ\n");
                    return; //0x0
                case RV64_FUNCT3_BNE  :
                    assert(0 && "RV64_OP_BRANCH - BNE\n");
                    return; //  0x1
                case RV64_FUNCT3_BLT  :
                    assert(0 && "RV64_OP_BRANCH - BLT\n");
                    return; //  0x4
                case RV64_FUNCT3_BGE  :
                    assert(0 && "RV64_OP_BRANCH - BGE\n");
                    return; //  0x5
                case RV64_FUNCT3_BLTU :
                    assert(0 && "RV64_OP_BRANCH - BLTU\n");
                    return; //  0x6
                case RV64_FUNCT3_BGEU :
                    assert(0 && "RV64_OP_BRANCH - BGEU\n");
                    return; //  0x7
            }
            return 0; //0x63    /* 1100011 */

        case RV64_OP_JALR:
            write_reg_long(instruction.i_type.rd, PC + 4);
            PC = read_reg_long(instruction.i_type.rs1);
            return PC; //0x67    /* 1100111 */

        case RV64_OP_JAL:
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
    printf("%d\t%8x:\t%8x\t", inst_count, PC, instruction.instruction);
    switch(instruction.encoding.opcode)
    {
        case RV64_OP_LOAD:
            switch (instruction.i_type.funct3) {
                case RV64_FUNCT3_LB  :
                    assert(0 && "RV64_OP_LOAD - LB\n");
                    return; //0x0
                case RV64_FUNCT3_LH  :
                    assert(0 && "RV64_OP_LOAD - LH\n");
                    return; //0x1
                case RV64_FUNCT3_LW  :
                    assert(0 && "RV64_OP_LOAD - LW\n");
                    return; //0x2
                case RV64_FUNCT3_LBU :
                    assert(0 && "RV64_OP_LOAD - LBU\n");
                    return; //0x4
                case RV64_FUNCT3_LHU :
                    assert(0 && "RV64_OP_LOAD - LHU\n");
                    return; //0x5
                case RV64_FUNCT3_LWU :
                    assert(0 && "RV64_OP_LOAD - LWU\n");
                    return; //0x6
                case RV64_FUNCT3_LD  :
                    printf("ld\t$r%d, %d($r%d)\n", instruction.i_type.rd, i_imm(instruction.i_type), instruction.i_type.rs1);
                    return; //0x3
            }
            assert(0 && "UNKNOWN LOAD OP");
            return 0; //0x03    /* 0000011 */
        case RV64_OP_LOAD_FP:
            assert(0 && "RV64_OP_LOAD_FP\n");
            return 0; //0x07    /* 0000111 */
        case RV64_OP_MISC_MEM:
            assert(0 && "RV64_OP_MISC_MEM\n");
            return 0; //0x0f    /* 0001111 */

        case RV64_OP_OP_IMM:
            switch(instruction.i_type.funct3)
            {
                case RV64_FUNCT3_ADDI :
                    printf("addi\t$r%d, $r%d, %d\n", instruction.i_type.rd, instruction.i_type.rs1, i_imm(instruction.i_type));
                    return;// 0x0
                case RV64_FUNCT3_SLTI :
                    assert(0 && "RV64_OP_OP_IMM - SLTI\n");
                    return;// 0x2
                case RV64_FUNCT3_SLTIU:
                    assert(0 && "RV64_OP_OP_IMM - SLTIU\n");
                    return;// 0x3
                case RV64_FUNCT3_XORI :
                    assert(0 && "RV64_OP_OP_IMM - XORI\n");
                    return;// 0x4
                case RV64_FUNCT3_ORI  :
                    assert(0 && "RV64_OP_OP_IMM - ORI\n");
                    return;// 0x6

                case RV64_FUNCT3_ANDI :
                    printf("andi\t$r%d, $r%d, %d\n", instruction.i_type.rd, instruction.i_type.rs1, i_imm(instruction.i_type));
                    return;// 0x7

                case RV64_FUNCT3_SLLI :
                    printf("slli\t$r%d, $r%d, %d\n", instruction.is_type.rd, instruction.is_type.rs1, is_imm_64(instruction.is_type));
                    return;

                case RV64_FUNCT3_SRLI :
                    assert(0 && "RV64_OP_OP_IMM - SRLI\n");
                    return; //0x5
            }

            return 0; //0x13    /* 0010011 */

        case RV64_OP_AUIPC:
            printf("auipc\t$r%d, 0x%lx\n", instruction.u_type.rd, (u_imm(instruction.u_type) << 12) + PC);
            return; //0x17    /* 0010111 */

        case RV64_OP_OP_IMM32:
            assert(0 && "RV64_OP_OP_IMM32\n");
            return 0; //0x1b    /* 0011011 */
        case RV64_OP_STORE:
            switch (instruction.s_type.funct3) {
                case RV64_FUNCT3_SB :
                    assert(0 && "RV64_OP_STORE - SB\n");
                    return; //0x0
                case RV64_FUNCT3_SH :
                    assert(0 && "RV64_OP_STORE - SH\n");
                    return; //0x1
                case RV64_FUNCT3_SW :
                    assert(0 && "RV64_OP_STORE - SW\n");
                    return; //0x2
                case RV64_FUNCT3_SD:
                    printf("sd\t $r%d, %d($r%d)\n", instruction.s_type.rs2, s_imm(instruction.s_type), instruction.s_type.rs1);
                    return; //0x3
            }
            assert(0 && "RV64_OP_STORE\n");
            return 0; //0x23    /* 0100011 */
        case RV64_OP_STORE_FP:
            assert(0 && "RV64_OP_STORE_FP\n");
            return 0; //0x27    /* 0100111 */
        case RV64_OP_AMO:
            assert(0 && "RV64_OP_AMO\n");
            return 0; //0x2f    /* 0101111 */
        case RV64_OP_OP:
            switch(instruction.r_type.funct3)
            {

                case RV64_FUNCT3_ADD   :
                    switch(instruction.r_type.funct7)
                    {
                        case RV64_FUNCT7_ADD :
                            printf("add\t$r%d, $r%d, $r%d\n", instruction.r_type.rd, instruction.r_type.rs1, instruction.r_type.rs2);
                            return; //0x00
                        case RV64_FUNCT7_SUB :
                            assert(0 && "RV64_OP_OP - SUB\n");
                            return PC + 4; //0x20
                    }

                case RV64_FUNCT3_SLL   :
                    assert(0 && "RV64_OP_OP - SLL\n");
                    return PC + 4; // 0x1
                case RV64_FUNCT3_SLT   :
                    assert(0 && "RV64_OP_OP - SLT\n");
                    return PC + 4; // 0x2
                case RV64_FUNCT3_SLTU  :
                    assert(0 && "RV64_OP_OP - SLTU\n");
                    return PC + 4; // 0x3
                case RV64_FUNCT3_XOR   :
                    assert(0 && "RV64_OP_OP - XOR\n");
                    return PC + 4; // 0x4
                case RV64_FUNCT3_SRL   :
                    assert(0 && "RV64_OP_OP - SRL\n");
                    return PC + 4; // 0x5
                case RV64_FUNCT3_OR    :
                    assert(0 && "RV64_OP_OP - OR\n");
                    return PC + 4; // 0x6
                case RV64_FUNCT3_AND   :
                    assert(0 && "RV64_OP_OP - AND\n");
                    return PC + 4; // 0x7
            }
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
            switch(instruction.b_type.funct3)
            {
                case RV64_FUNCT3_BEQ  :
                    assert(0 && "RV64_OP_BRANCH - BEQ\n");
                    return; //0x0
                case RV64_FUNCT3_BNE  :
                    printf("bne $r%d, $r%d, %d\n", instruction.b_type.rs1, instruction.b_type.rs2, b_imm(instruction.b_type));
                    return; //  0x1
                case RV64_FUNCT3_BLT  :
                    assert(0 && "RV64_OP_BRANCH - BLT\n");
                    return; //  0x4
                case RV64_FUNCT3_BGE  :
                    assert(0 && "RV64_OP_BRANCH - BGE\n");
                    return; //  0x5
                case RV64_FUNCT3_BLTU :
                    assert(0 && "RV64_OP_BRANCH - BLTU\n");
                    return; //  0x6
                case RV64_FUNCT3_BGEU :
                    assert(0 && "RV64_OP_BRANCH - BGEU\n");
                    return; //  0x7
            }
            assert(0 && "RV64_OP_BRANCH\n");
            return 0; //0x63    /* 1100011 */

        case RV64_OP_JALR:
            printf("jalr\t$r%d, %d($r%d)\n", instruction.i_type.rd, i_imm(instruction.i_type), instruction.i_type.rs1, 0);
            return 0; //0x67    /* 1100111 */

        case RV64_OP_JAL:
            uint64_t imm = j_imm(instruction.j_type);
            printf("jal\t$r%d, 0x%x\n", instruction.j_type.rd, PC + imm);
            return; //0x6f    /* 1101111 */

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
        val = 0xFFFFFFFFFFFFl;
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
        val = 0xFFFFFFFFFFFFl;
        return (val << 20) | u.imm;
    }

    return u.sext << 20 | u.imm;
}

uint64_t i_imm(i_inst_t i)
{
    uint64_t val = 0;
    if(i.sext == 1)
    {
        val = 0xFFFFFFFFFFFFl;
    }

    return val << 11 | i.imm;
}

uint64_t is_imm_64(is_inst_t i)
{
    return i.shamt_ext << 6 | i.shamt;//val << 11 | i.imm;
}

uint32_t is_imm_32(is_inst_t i)
{
    return 0;
}

uint64_t s_imm(s_inst_t s)
{
    uint64_t val = 0;
    if(s.sext == 1)
    {
        val = 0xFFFFFFFFFFFFl;
    }

    return val << 11 | s.imm2 << 5 | s.imm1;
}

uint64_t b_imm(b_inst_t b)
{
    uint64 val = 0;
    if(b.sext == 1)
    {
        val = 0xFFFFFFFFFFFFl;
    }

    return val << 12 | b.imm3 << 11 | b.imm2 << 5 | b.imm1;

}

