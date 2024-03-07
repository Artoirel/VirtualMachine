#include "memory.h"
#include <math.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "address_type.h"

void write_byte(uint64_t addr, uint8_t byte)
{
    address_t address;
    address.address = addr;

    int aligned = check_addr_aligned(addr, 1);
    if(aligned > 0)
    {
        THROW_ERROR("Address unaligned");
    }

    validate_mem_alloc(address);

    vmem[address.L1][address.L2][address.L3][address.L4][address.offset] = byte;
}

void write_half(uint64_t addr, uint16_t half)
{
    address_t address;
    address.address = addr;

    data_bytes_type data;
    data.data = (uint64_t) half;

    int aligned = check_addr_aligned(addr, 2);
    if(aligned > 0)
    {
        THROW_ERROR("Address unaligned");
    }

    validate_mem_alloc(address);

    write_byte(addr, data.bytes.b1);
    write_byte(addr + 1, data.bytes.b2);
}

void write_word(uint64_t addr, uint32_t word)
{
    address_t address;
    address.address = addr;

    data_bytes_type data;
    data.data = (uint64_t) word;

    int aligned = check_addr_aligned(addr, 4);
    if(aligned > 0)
    {
        THROW_ERROR("Address unaligned");
    }

    validate_mem_alloc(address);

    write_half(addr, )
}
void write_double_word(uint64_t addr, uint64_t double_word);

uint8_t read_byte(uint64_t addr);
uint16_t read_half(uint64_t addr);
uint32_t read_word(uint64_t addr);
uint64_t read_double_word(uint64_t addr);

int check_addr_aligned(uint64_t addr, int size)
{
    return addr % size;
}

void validate_mem_alloc(address_t address)
{
    if(vmem == null)
    {
        vmem = (uint8_t*****) malloc(sizeof(uint8_t*****) * 2^9);
        for(int i = 0; i < 2^9; i++)
        {
            vmem[i] = NULL;
        }
    }

    if(vmem[address.bits.L1] == NULL)
    {
        vmem[address.bits.L1] = (uint8_t****) malloc(sizeof(uint8_t****) * 2^9);
        for(int i = 0; i < 2^9; i++)
        {
            vmem[address.bits.L1][i] = NULL;
        }
    }

    if(vmem[address.bits.L1][address.bits.L2] == NULL)
    {
        vmem[address.bits.L1][address.bits.L2] = (uint8_t***) malloc(sizeof(uint8_t***) * 2^9);
        for(int i = 0; i < 2^9; i++)
        {
            vmem[address.bits.L1][address.bits.L2][i] = NULL;
        }
    }

    if(vmem[address.bits.L1][address.bits.L2][address.bits.L3] == NULL)
    {
        vmem[address.bits.L1][address.bits.L2][address.bits.L3] = (uint8_t**) malloc(sizeof(uint8_t**) * 2^9);
        for(int i = 0; i < 2^9; i++)
        {
            vmem[address.bits.L1][address.bits.L2][address.bits.L3][i] = NULL;
        }
    }

    if(vmem[address.bits.L1][address.bits.L2][address.bits.L3][address.bits.L4] == NULL)
    {
        vmem[address.bits.L1][address.bits.L2][address.bits.L3][address.bits.L4] = (uint8_t*) malloc(sizeof(uint8_t*) * 2^12);
        for(int i = 0; i < 2^12; i++)
        {
            vmem[address.bits.L1][address.bits.L2][address.bits.L3][address.bits.L4][i] = NULL;
        }
    }
}