#include "memory.h"
#include <math.h>
#include <stdio.h>
#include "address_type.h"

void init_page(uint64_t page[], uint64_t pagesize)
{
    if(!page)
    {
        for(int i = 0; i < 2^9; i++)
        {
            page[i] = NULL;
        }
    }
}

void write_byte(uint64_t addr, uint8_t byte)
{
    //address_t address;
    /address.address = addr;




}
void write_half(uint64_t addr, uint16_t half);
void write_word(uint64_t addr, uint32_t word);
void write_double_word(uint64_t addr, uint64_t double_word);

uint8_t read_byte(uint64_t addr);
uint16_t read_half(uint64_t addr);
uint32_t read_word(uint64_t addr);
uint64_t read_double_word(uint64_t addr);

int check_addr_aligned(uint64_t addr);