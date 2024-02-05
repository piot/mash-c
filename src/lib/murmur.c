#include <mash/murmur.h>

#define MASH_ROTATE_LEFT_32_BIT(x, r) ((x << r) | (x >> (32 - r)))

/// Code based on the public domain code by Austin Appleby.
/// source: https://github.com/aappleby/smhasher/blob/master/src/MurmurHash3.cpp
/// @param data data to calculate hash on
/// @param octetCount number of octets in data
/// @return the 32 bit hash
uint32_t mashMurmurHash3(const uint8_t* data, size_t octetCount)
{
    const uint32_t c1 = 0xcc9e2d51;
    const uint32_t c2 = 0x1b873593;
    const uint32_t c3 = 0x85ebca6b;
    const uint32_t c4 = 0xc2b2ae35;
    const uint32_t c5 = 0xe6546b64;

    const int nblocks = (int) octetCount / 4;
    const uint32_t* blocks = (const uint32_t*)(data + nblocks * 4);
    uint32_t h1 = 0; // TODO: can use a seed here

    for (int i = -nblocks; i; i++) {
        uint32_t k1 = blocks[i];
        k1 *= c1;
        k1 = MASH_ROTATE_LEFT_32_BIT(k1, 15);
        k1 *= c2;
        h1 ^= k1;
        h1 = MASH_ROTATE_LEFT_32_BIT(h1, 13);
        h1 = h1 * 5 + c5;
    }

    const uint8_t* tail = (const uint8_t*)(data + nblocks * 4);
    uint32_t k1 = 0;

    switch (octetCount & 3) {
    case 3:
        k1 ^= (uint32_t)tail[2] << 16;
        __attribute__((fallthrough));
    case 2:
        k1 ^= (uint32_t)tail[1] << 8;
        __attribute__((fallthrough));
    case 1:
        k1 ^= tail[0];
        k1 *= c1;
        k1 = MASH_ROTATE_LEFT_32_BIT(k1, 15);
        k1 *= c2;
        h1 ^= k1;
    }

    h1 ^= octetCount;
    h1 ^= h1 >> 16;
    h1 *= c3;
    h1 ^= h1 >> 13;
    h1 *= c4;
    h1 ^= h1 >> 16;

    return h1;
}
