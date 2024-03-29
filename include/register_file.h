#ifndef __REGISTER_FILE_H__
#define __REGISTER_FILE_H__

#include "rf_contents_type.h"
#include <stdint.h>

void init_rf(uint64_t sp);

void write_fp_reg_double(uint8_t reg, double value);
void write_fp_reg_float(uint8_t reg, float value);

void write_reg_word(uint8_t reg, uint32_t value);
void write_reg_long(uint8_t reg, uint64_t value);

float read_fp_reg_float(uint8_t reg);
double read_fp_reg_double(uint8_t reg);
uint32_t read_fp_reg_int(uint8_t reg);
uint64_t read_fp_reg_long(uint8_t reg);

float read_reg_float(uint8_t reg);
double read_reg_double(uint8_t reg);
uint32_t read_reg_int(uint8_t reg);
uint64_t read_reg_long(uint8_t reg);

#endif
