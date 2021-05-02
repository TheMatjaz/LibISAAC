/**
 * @file
 *
 * Test suite runner of LibISAAC.
 *
 * @copyright Copyright © 2020-2021, Matjaž Guštin <dev@matjaz.it>
 * <https://matjaz.it>. All rights reserved.
 * @license BSD 3-clause license.
 */

#include "test.h"

int main(void)
{
    test_isaac_init();
    test_isaac_next();
    test_isaac_convert();
    test_isaac_cleanup();
    return atto_at_least_one_fail;
}
