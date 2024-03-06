#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdint.h>
#include <stddef.h>

uint8_t *****vmem = NULL;

void init_page(uint64_t page[], uint64_t pagesize);

void write_byte(uint64_t addr, uint8_t byte);
void write_half(uint64_t addr, uint16_t half);
void write_word(uint64_t addr, uint32_t word);
void write_double_word(uint64_t addr, uint64_t double_word);

uint8_t read_byte(uint64_t addr);
uint16_t read_half(uint64_t addr);
uint32_t read_word(uint64_t addr);
uint64_t read_double_word(uint64_t addr);

int check_addr_aligned(uint64_t addr);

#endif
