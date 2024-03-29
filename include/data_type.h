#ifndef __DATA_TYPE_H__
#define __DATA_TYPE_H__

#include <stdint.h>

typedef struct data_bytes_type
{
    uint8_t b1;
    uint8_t b2;
    uint8_t b3;
    uint8_t b4;
    uint8_t b5;
    uint8_t b6;
    uint8_t b7;
    uint8_t b8;
} data_bytes_t;

typedef struct data_half_type
{
    uint16_t h1;
    uint16_t h2;
    uint16_t h3;
    uint16_t h4;
} data_half_t;

typedef struct data_word_type
{
    uint32_t w1;
    uint32_t w2;
} data_word_t;

typedef union data_type
{
    uint64_t data;
    data_word_t words;
    data_half_t halfs;
    data_bytes_t bytes;
} data_t;

#endif
