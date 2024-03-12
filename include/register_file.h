#ifndef __REGISTER_FILE_H__
#define __REGISTER_FILE_H__

#include "rf_contents_type.h"
#include <stdint.h>

void init_rf();

void write_fp_reg(uint8_t reg, uint64_t value);
void write_reg(uint_t reg, uint64_t value);

rf_contents_t read_fp_reg(uint8_t reg);
rf_contents_t read_reg(uint8_t reg);

#endif
