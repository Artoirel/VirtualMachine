#include "register_file.h"
#include "rf_contents_type.h"

rf_contents_t reg_file[32];
rf_contents_t fp_reg_file[32];

void init_rf()
{
    for(int i = 0; i < 32; i++)
    {
        reg_file[i] = 0;
    }

    for(int i = 0; i < 32; i++)
    {
        fp_reg_file[i] = 0;
    }
}

void wrote_fp