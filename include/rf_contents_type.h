#ifndef __RF_CONTENTS_TYPE_H__
#define __RF_CONTENTS_TYPE_H__

#include "rf_contents_type.h"

typedef union {
    float fpsingle;
    double fpdouble;
    uint32_t intword;
    uint64_t intdouble;
} rf_contents_t;

#endif
