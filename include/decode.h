#ifndef __DECODE_H__
#define __DECODE_H__

#include <stdint.h>
#include "inst_type.h"

void decode_loop(uint64_t PC);

int dispatch(inst_t instruction, uint64_t PC);

void pretty_print(inst_t instruction, uint64_t PC);

uint64_t j_imm(j_inst_t j);

uint64_t u_imm(u_inst_t u);

#endif
