#ifndef __DECODE_H__
#define __DECODE_H__

#include <stdint.h>

int decode_loop(uint64_t PC);

int dispatch(inst_t instruction);

#endif
