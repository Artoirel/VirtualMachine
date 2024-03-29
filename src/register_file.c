#include "register_file.h"
#include "rf_contents_type.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

rf_contents_t reg_file[32];
rf_contents_t fp_reg_file[32];

void init_rf(uint64_t sp)
{
    for(int i = 0; i < 32; i++)
    {
        reg_file[i].intdouble = 0;
    }

    reg_file[2].intdouble = sp_data;

    for(int i = 0; i < 32; i++)
    {
        fp_reg_file[i].intdouble = 0;
    }
}

void write_fp_reg_double(uint8_t reg, double value)
{
    fp_reg_file[reg].fpdouble = value;
}

void write_fp_reg_float(uint8_t reg, float value)
{
    fp_reg_file[reg].fpfloat = value;
}

void write_reg_word(uint8_t reg, uint32_t value)
{
    if(reg == 0) return;
    reg_file[reg].intword = value;
}

void write_reg_long(uint8_t reg, uint64_t value)
{
    if(reg == 0) return;
    reg_file[reg].intword = value;
}

float read_fp_reg_float(uint8_t reg)
{
    return fp_reg_file[reg].fpsingle;
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
    return reg_file[reg].fpsingle;
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