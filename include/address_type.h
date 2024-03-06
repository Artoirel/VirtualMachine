#ifndef __ADDRESS_TYPE_H__
#define __ADDRESS_TYPE_H__

#include <stdint.h>

typedef struct address_type
{
    uint64_t address;
    uint64_t L1 : 9 = (address >> 38) & 0x1ff;
    uint64_t L2 : 9 = (address >> 29) & 0x1ff;
    uint64_t L3 : 9 = (address >> 20) & 0x1ff;
    uint64_t L4 : 9 = (address >> 11) & 0x1ff;
    uint64_t offest : 12 = address & 0xfff;
} address_t;

#endif //VIRTUALMACHINE_ADDRESS_TYPE_H
