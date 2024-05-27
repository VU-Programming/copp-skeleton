#include "util.h"
#include <stdio.h>
// Endianness helper functions

uint32_t swap_uint32(uint32_t num)
{
  return ((num >> 24) & 0xff) | ((num << 8) & 0xff0000) |
         ((num >> 8) & 0xff00) | ((num << 24) & 0xff000000);
}

uint16_t swap_uint16(uint16_t num)
{
  return ((num >> 8) & 0xff) | ((num << 8) & 0xff00);
}

int16_t swap_int16(int16_t num) {
  return (int16_t)swap_uint16((uint16_t)num);
}

int32_t swap_int32(int32_t num) {
  return (int32_t)swap_uint32((uint32_t)num);
}

uint32_t read_uint32(uint8_t *buf)
{
  return ((uint32_t)buf[0] << 24) | ((uint32_t)buf[1] << 16) |
         ((uint32_t)buf[2] << 8) | (uint32_t)buf[3];
}

uint16_t read_uint16(uint8_t *buf)
{
  return (uint16_t)((uint16_t)buf[0] << 8) | (uint16_t)buf[1];
}


int32_t read_int32(uint8_t* buf) {
  return (int32_t) read_uint32(buf);
}

int16_t read_int16(uint8_t* buf) {
  return (int16_t) read_uint16(buf);
}
