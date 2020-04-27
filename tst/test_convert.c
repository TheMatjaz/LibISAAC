/**
 * @file
 *
 * Test suite of LibISAAC
 *
 * @copyright Copyright © 2020, Matjaž Guštin <dev@matjaz.it>
 * <https://matjaz.it>. All rights reserved.
 * @license BSD 3-clause license.
 */

#include "test.h"

#if ISAAC_BITS > 32

static void test_to_little_endian(void)
{
    const uint64_t values[2] = {0x0102030405060708ULL, 0xAABBCCDD11223344ULL};
    uint8_t bytes[16] = {0};

    isaac_to_little_endian(bytes, values, 2);

    atto_eq(8, sizeof(uint64_t));
    atto_eq(bytes[0], 0x08);
    atto_eq(bytes[1], 0x07);
    atto_eq(bytes[2], 0x06);
    atto_eq(bytes[3], 0x05);
    atto_eq(bytes[4], 0x04);
    atto_eq(bytes[5], 0x03);
    atto_eq(bytes[6], 0x02);
    atto_eq(bytes[7], 0x01);
    atto_eq(bytes[8], 0x44);
    atto_eq(bytes[9], 0x33);
    atto_eq(bytes[10], 0x22);
    atto_eq(bytes[11], 0x11);
    atto_eq(bytes[12], 0xDD);
    atto_eq(bytes[13], 0xCC);
    atto_eq(bytes[14], 0xBB);
    atto_eq(bytes[15], 0xAA);
}

static void test_to_big_endian(void)
{
    const uint64_t values[2] = {0x0102030405060708ULL, 0xAABBCCDD11223344ULL};
    uint8_t bytes[2 * sizeof(uint64_t)] = {0};

    isaac_to_big_endian(bytes, values, 2);

    atto_eq(8, sizeof(uint64_t));
    atto_eq(bytes[0], 0x01);
    atto_eq(bytes[1], 0x02);
    atto_eq(bytes[2], 0x03);
    atto_eq(bytes[3], 0x04);
    atto_eq(bytes[4], 0x05);
    atto_eq(bytes[5], 0x06);
    atto_eq(bytes[6], 0x07);
    atto_eq(bytes[7], 0x08);
    atto_eq(bytes[8], 0xAA);
    atto_eq(bytes[9], 0xBB);
    atto_eq(bytes[10], 0xCC);
    atto_eq(bytes[11], 0xDD);
    atto_eq(bytes[12], 0x11);
    atto_eq(bytes[13], 0x22);
    atto_eq(bytes[14], 0x33);
    atto_eq(bytes[15], 0x44);
}
#else

static void test_to_little_endian(void)
{
    const uint32_t values[2] = {0x01020304UL, 0xAABBCCDDUL};
    uint8_t bytes[8] = {0};

    isaac_to_little_endian(bytes, values, 2);

    atto_eq(4, sizeof(uint32_t));
    atto_eq(bytes[0], 0x04);
    atto_eq(bytes[1], 0x03);
    atto_eq(bytes[2], 0x02);
    atto_eq(bytes[3], 0x01);
    atto_eq(bytes[4], 0xDD);
    atto_eq(bytes[5], 0xCC);
    atto_eq(bytes[6], 0xBB);
    atto_eq(bytes[7], 0xAA);
}

static void test_to_big_endian(void)
{
    const uint32_t values[2] = {0x01020304UL, 0xAABBCCDDUL};
    uint8_t bytes[2 * sizeof(uint32_t)] = {0};

    isaac_to_big_endian(bytes, values, 2);

    atto_eq(bytes[0], 0x01);
    atto_eq(bytes[1], 0x02);
    atto_eq(bytes[2], 0x03);
    atto_eq(bytes[3], 0x04);
    atto_eq(bytes[4], 0xAA);
    atto_eq(bytes[5], 0xBB);
    atto_eq(bytes[6], 0xCC);
    atto_eq(bytes[7], 0xDD);
}

#endif


void test_isaac_convert(void)
{
    test_to_little_endian();
    test_to_big_endian();
}
