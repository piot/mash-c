#ifndef MASH_MURMUR_3_H
#define MASH_MURMUR_3_H

#include <stdint.h>
#include <stddef.h>

uint32_t mashMurmurHash3(const uint8_t* data, size_t len);
uint32_t mashMurmurHash3WithSeed(const uint8_t* data, size_t octetCount, uint32_t seed);

#endif
