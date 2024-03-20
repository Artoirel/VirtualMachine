#include "register_file.h"
#include "rf_contents_type.h"
#include <stdio.h>
#include <stdint.h>

rf_contents_t reg_file[32];
rf_contents_t fp_reg_file[32];

void init_rf(uint64_t sp, uint64_t gp)
{
    for(int i = 0; i < 32; i++)
    {
        rf_contents_t value;
        value.intdouble = 0;
        reg_file[i] = value;
    }

    printf("here");

    rf_contents_t sp_data;
    sp_data.intdouble = sp;

    rf_contents_t gp_data;
    gp_data.intdouble = gp;

    reg_file[2] = sp_data;
    reg_file[3] = gp_data;

    for(int i = 0; i < 32; i++)
    {
        rf_contents_t value;
        value.intdouble = 0;
        fp_reg_file[i] = value;
    }
}

void write_fp_reg(uint8_t reg, rf_contents_t value)
{
    fp_reg_file[reg] = value;
}

void write_reg(uint8_t reg, rf_contents_t value)
{
    if(reg == 0) return;
    reg_file[reg] = value;
}

rf_contents_t read_fp_reg(uint8_t reg)
{
    return fp_reg_file[reg];
}

rf_contents_t read_reg(uint8_t reg)
{
    return reg_file[reg];
}