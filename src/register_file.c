#include "register_file.h"
#include "rf_contents_type.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

rf_contents_t *reg_file;
rf_contents_t *fp_reg_file;

void init_rf(uint64_t sp)
{
    reg_file = (rf_contents_t*) malloc(sizeof(rf_contents_t) * 32);
    fp_reg_file = (rf_contents_t*) malloc(sizeof(rf_contents_t) * 32);

    reg_file[0].intdouble = 0;

    write_reg_long(2, sp);
}

void write_fp_reg_double(uint8_t reg, double value)
{
    fp_reg_file[reg].fpdouble = value;
}

void write_fp_reg_float(uint8_t reg, float value)
{
    fp_reg_file[reg].fpfloat = value;
}

void write_reg_int(uint8_t reg, uint32_t value)
{
    if(reg == 0) return;
    printf("writing value - 0x%16x\n", value);
    reg_file[reg].intword = value;
}

void write_reg_long(uint8_t reg, uint64_t value)
{
    if(reg == 0) return;
    printf("writing value - 0x%16x\n", value);
    reg_file[reg].intdouble = value;
}

float read_fp_reg_float(uint8_t reg)
{
    return fp_reg_file[reg].fpfloat;
}

double read_fp_reg_double(uint8_t reg)
{
    return fp_reg_file[reg].fpdouble;
}

uint32_t read_fp_reg_int(uint8_t reg)
{
    return fp_reg_file[reg].intword;
}

uint64_t read_fp_reg_long(uint8_t reg)
{
    return fp_reg_file[reg].intdouble;
}

float read_reg_float(uint8_t reg)
{
    return reg_file[reg].fpfloat;
}

double read_reg_double(uint8_t reg)
{
    return reg_file[reg].fpdouble;
}

uint32_t read_reg_int(uint8_t reg)
{
    return reg_file[reg].intword;
}

uint64_t read_reg_long(uint8_t reg)
{
    return reg_file[reg].intdouble;
}

void print_reg(uint8_t reg)
{
    printf("0x%8x%8x\n", read_reg_long(reg) >> 32, read_reg_long(reg) & 0xffffffff);
}

void print_fp_reg(uint8_t reg)
{
    printf("0x%8x%8x\n", read_fp_reg_long(reg) >> 32, read_fp_reg_long(reg) & 0xffffffff);
}