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

void write_fp_reg(uint8_t reg, rf_contents_t *value)
{
    rf_contents_t *temp = fp_reg_file[reg];
    fp_reg_file[reg] = value;
    free(temp);
}

void write_reg(uint8_t reg, rf_contents_t *value)
{
    if(reg == 0) return;
    rf_contents_t *temp = reg_file[reg];
    reg_file[reg] = value;
    free(temp);
}

rf_contents_t *read_fp_reg(uint8_t reg)
{
    return fp_reg_file[reg];
}

rf_contents_t *read_reg(uint8_t reg)
{
    return reg_file[reg];
}