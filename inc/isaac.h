/**
 * @file
 *
 * ISAAC, the fast cryptographic pseudo random number generator (CPRNG) wrapped
 * into a C11, modern, documented API and package. Quoting from its
 * [web page](https://www.burtleburtle.net/bob/rand/isaacafa.html):
 *
 * > ISAAC (Indirection, Shift, Accumulate, Add, and Count) generates 32-bit
 * > random numbers. Averaged out, it requires 18.75 machine cycles to
 * > generate each 32-bit value. Cycles are guaranteed to be at least 240
 * > values long, and they are 28295 values long on average. The results are
 * > uniformly distributed, unbiased, and unpredictable unless you know the
 * > seed.
 *
 * ISAAC and its original source code is created by Bob Jenkins and
 * released into the public domain.
 *
 * @copyright Copyright © 2020, Matjaž Guštin <dev@matjaz.it>
 * <https://matjaz.it>. All rights reserved.
 * @license BSD 3-clause license.
 */

#ifndef ISAAC_H
#define ISAAC_H

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Version of the isaac.h API using semantic versioning.
 */
#define LIBISAAC_VERSION "1.0.0"

#include <stdint.h>
#include <stdbool.h>

#define ISAAC_SIZE 256U

/* Context of random number generator */
typedef struct {
    uint32_t cnt;
    uint32_t rsl[ISAAC_SIZE];
    uint32_t mem[ISAAC_SIZE];
    uint32_t a;
    uint32_t b;
    uint32_t c;
} isaac_ctx_t;

//  If (flag==TRUE), then use the contents of randrsl[0..RANDSIZ-1] as the seed.
/**
 * Initialises the ISAAC CPRNG.
 *
 * Uses the `rsl` field as initial seed
 *
 * @param ctx
 * @param flag
 */
void isaac_init(isaac_ctx_t* ctx, bool flag);
uint32_t isaac_next(isaac_ctx_t* ctx);


#ifdef __cplusplus
}
#endif

#endif  /* ISAAC_H */
