#ifndef __RF_CONTENTS_TYPE_H__
#define __RF_CONTENTS_TYPE_H__

#include <stdint.h>

typedef union rf_contents_type {
    float fpfloat;
    double fpdouble;
    uint32_t intword;
    uint64_t intdouble;
} rf_contents_t;

#endif
