#ifndef __ADDRESS_TYPE_H__
#define __ADDRESS_TYPE_H__

#include <stdint.h>

typedef union address_type
{
    uint64_t address;
    struct{
        uint64_t offest : 12;
        uint64_t L4 : 9;
        uint64_t L3 : 9;
        uint64_t L2 : 9;
        uint64_t L1 : 9;
    } bits;
} address_t;

#endif //VIRTUALMACHINE_ADDRESS_TYPE_H
