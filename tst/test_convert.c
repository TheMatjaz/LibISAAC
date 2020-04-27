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

static void test_to_little_endian(void)
{
    const uint32_t values[2] = {0x01020304UL, 0xAABBCCDDUL};
    uint8_t bytes[8] = {0};

    isaac_uint32_to_little_endian(bytes, values, 2);

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

    isaac_uint32_to_big_endian(bytes, values, 2);

    atto_eq(bytes[0], 0x01);
    atto_eq(bytes[1], 0x02);
    atto_eq(bytes[2], 0x03);
    atto_eq(bytes[3], 0x04);
    atto_eq(bytes[4], 0xAA);
    atto_eq(bytes[5], 0xBB);
    atto_eq(bytes[6], 0xCC);
    atto_eq(bytes[7], 0xDD);
}

void test_isaac_convert(void)
{
    test_to_little_endian();
    test_to_big_endian();
}
