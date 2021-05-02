/**
 * @file
 *
 * Test suite of LibISAAC, testing isaac_cleanup().
 *
 * @copyright Copyright © 2020-2021, Matjaž Guštin <dev@matjaz.it>
 * <https://matjaz.it>. All rights reserved.
 * @license BSD 3-clause license.
 */

#include "test.h"

static void test_cleanup_null(void)
{
    isaac_cleanup(NULL);
}


static void test_cleanup(void)
{
    isaac_ctx_t ctx;
    memset(&ctx, 0xFFU, sizeof(ctx));

    isaac_cleanup(&ctx);

    atto_zeros((uint8_t*) &ctx, sizeof(ctx));
}

void test_isaac_cleanup(void)
{
    test_cleanup_null();
    test_cleanup();
}
