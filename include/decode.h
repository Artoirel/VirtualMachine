#ifndef __DECODE_H__
#define __DECODE_H__

#include <stdint.h>
#include "inst_type.h"

void decode_loop(uint64_t PC);

int dispatch(inst_t instruction, uint64_t PC);

void pretty_print(inst_t instruction, uint64_t PC);

uint32_t j_imm(j_inst_t j);

#endif
