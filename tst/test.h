/**
 * @file
 *
 * @copyright Copyright © 2020, Matjaž Guštin <dev@matjaz.it>
 * <https://matjaz.it>. All rights reserved.
 * @license BSD 3-clause license.
 */

#ifndef TEST_H
#define TEST_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>
#include "isaac.h"
#include "atto.h"
#include <stdio.h>
#include <inttypes.h>

void test_isaac_init(void);
void test_isaac_next(void);

#ifdef __cplusplus
}
#endif

#endif  /* TEST_H */
