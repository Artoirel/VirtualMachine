#ifndef __DECODE_H__
#define __DECODE_H__

#include <stdint.h>
#include "inst_type.h"

void decode_loop(uint64_t PC);

int dispatch(inst_t instruction, uint64_t PC);

void pretty_print(inst_t instruction, uint64_t PC);

uint64_t j_imm(j_inst_t j);

uint64_t u_imm(u_inst_t u);

uint64_t i_imm(i_inst_t i);

uint64_t is_imm(is_inst_t i);

uint64_t is_imm_64(is_inst_t i);

uint32_t is_imm_32(is_inst_t i);

uint64_t s_imm(s_inst_t s);

uint64_t b_imm(b_inst_t b);

#endif
