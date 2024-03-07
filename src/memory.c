#include "memory.h"
#include <math.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "address_type.h"
#include "error.h"

uint8_t *****vmem = NULL;

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

    vmem[address.bits.L1][address.bits.L2][address.bits.L3][address.bits.L4][address.bits.offset] = byte;
}

void write_half(uint64_t addr, uint16_t half)
{
    address_t address;
    address.address = addr;

    data_t data;
    data.data = (uint64_t) half;

    int aligned = check_addr_aligned(addr, 2);
    if(aligned > 0)
    {
        THROW_ERROR("Address unaligned");
    }

    write_byte(addr, data.bytes.b1);
    write_byte(addr + 1, data.bytes.b2);
}

void write_word(uint64_t addr, uint32_t word)
{
    address_t address;
    address.address = addr;

    data_t data;
    data.data = (uint64_t) word;

    int aligned = check_addr_aligned(addr, 4);
    if(aligned > 0)
    {
        THROW_ERROR("Address unaligned");
    }

    write_half(addr, data.halfs.h1);
    write_half(addr + 2, data.halfs.h2);
}
void write_double_word(uint64_t addr, uint64_t double_word)
{
    address_t address;
    address.address = addr;

    data_t data;
    data.data = (uint64_t) double_word;

    int aligned = check_addr_aligned(addr, 8);
    if(aligned > 0)
    {
        THROW_ERROR("Address unaligned");
    }

    write_word(addr, data.words.w1);
    write_word(addr + 4, data.words.w2);
}

uint8_t read_byte(uint64_t addr)
{
    int aligned = check_addr_aligned(addr, 1);
    if(aligned > 0)
    {
        THROW_ERROR("Address unaligned");
    }

    address_t address;
    data_t data;

    address.address = addr;
    return vmem[address.bits.L1][address.bits.L2][address.bits.L3][address.bits.L4][address.bits.offset];
}
uint16_t read_half(uint64_t addr)
{
    int aligned = check_addr_aligned(addr, 2);
    if(aligned > 0)
    {
        THROW_ERROR("Address unaligned");
    }

    data_t data;

    data.bytes.b1 = read_byte(addr);
    data.bytes.b2 = read_byte(addr + 1);

    return (uint16_t) data.data;
}

uint32_t read_word(uint64_t addr)
{
    int aligned = check_addr_aligned(addr, 4);
    if(aligned > 0)
    {
        THROW_ERROR("Address unaligned");
    }

    data_t data;

    data.halfs.h1 = read_half(addr);
    data.halfs.h2 = read_half(addr + 2);

    return (uint32_t) data.data;
}

uint64_t read_double_word(uint64_t addr)
{
    int aligned = check_addr_aligned(addr, 8);
    if(aligned > 0)
    {
        THROW_ERROR("Address unaligned");
    }

    data_t data;

    data.words.w1 = read_word(addr);
    data.words.w2 = read_word(addr + 4);

    return data.data;
}

int check_addr_aligned(uint64_t addr, int size)
{
    return addr % size;
}

void validate_mem_alloc(address_t address)
{
    if(vmem == NULL)
    {
        vmem = (uint8_t*****) malloc(sizeof(uint8_t*****) * 512);
        printf("Before global allocation\n");
        for(int i = 0; i < 512; i++)
        {
            vmem[i] = NULL;
            printf("%d\n", i);
        }
        printf("After first loop\n");
    }

    if(vmem[address.bits.L1] == NULL)
    {
        vmem[address.bits.L1] = (uint8_t****) malloc(sizeof(uint8_t****) * 512);
        for(int i = 0; i < 512; i++)
        {
            vmem[address.bits.L1][i] = NULL;
        }
        printf("After second loop\n");
    }

    if(vmem[address.bits.L1][address.bits.L2] == NULL)
    {
        vmem[address.bits.L1][address.bits.L2] = (uint8_t***) malloc(sizeof(uint8_t***) * 512);
        for(int i = 0; i < 512; i++)
        {
            vmem[address.bits.L1][address.bits.L2][i] = NULL;
        }
        printf("After 3rd loop\n");
    }

    if(vmem[address.bits.L1][address.bits.L2][address.bits.L3] == NULL)
    {
        vmem[address.bits.L1][address.bits.L2][address.bits.L3] = (uint8_t**) malloc(sizeof(uint8_t**) * 512);
        for(int i = 0; i < 512; i++)
        {
            vmem[address.bits.L1][address.bits.L2][address.bits.L3][i] = NULL;
        }
        printf("After 4th loop\n");
    }

    if(vmem[address.bits.L1][address.bits.L2][address.bits.L3][address.bits.L4] == NULL)
    {
        vmem[address.bits.L1][address.bits.L2][address.bits.L3][address.bits.L4] = (uint8_t*) malloc(sizeof(uint8_t*) * 4096);
        for(int i = 0; i < 4096; i++)
        {
            vmem[address.bits.L1][address.bits.L2][address.bits.L3][address.bits.L4][i] = NULL;
        }
        printf("After final loop\n");
    }
}