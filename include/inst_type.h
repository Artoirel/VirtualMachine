#ifndef __INST_TYPE_H__
#define __INST_TYPE_H__

typedef union instruction_type
{
    uint32_t instruction;
    encoding_t encoding;
    r_inst_t r_type;
    i_inst_t i_type;
    s_inst_t s_type;
    b_inst_t b_type;
    u_inst_t u_type;
    j_inst_t j_type;

} inst_t;

typedef struct encoding_type
{
    uint8_t opcode : 7
} encoding_t;

typedef struct r_instruction_type
{
    uint8_t opcode : 7
    uint8_t rd : 5
    uint8_t funct3 : 3
    uint8_t rs1 : 5
    uint8_t rs2 : 5
    uint8_t funct7 : 7
} r_inst_t;

typedef struct i_instruction_type
{
    uint8_t opcode : 7
    uint8_t rd : 5
    uint8_t funct3 : 3
    uint8_t rs1 : 5
    uint16_t imm : 12
} i_inst_t;

typedef struct s_type_instruction
{
    uint8_t opcode : 7
    uint8_t imm1 : 5
    uint8_t funct3 : 3
    uint8_t rs1 : 5
    uint8_t rs2 : 5
    uint8_t imm2 : 7
} s_inst_t;

typedef struct b_instruction_type
{
    uint8_t opcode : 7
    uint8_t imm3 : 1
    uint8_t imm1 : 4
    uint8_t funct3 : 3
    uint8_t rs1 : 5
    uint8_t rs2 : 5
    uint8_t imm2 : 6
    uint8_t imm4 : 1
} b_inst_t;

typedef struct u_instruction_type
{
    uint8_t opcode : 7
    uint8_t rd : 5
    uint32_t imm : 20
} u_inst_t;

typedef struct j_instruction_type
{
    uint8_t opcode : 7
    uint8_t rd : 5
    uint32_t imm3 : 8
    uint32_t imm2 : 1
    uint32_t imm1 : 10
    uint32_t imm4 : 1

} j_inst_t;

#endif
