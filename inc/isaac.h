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
 * This implementation is based on the `randport.c` implementation, which uses
 * 32-bit words while being portable onto 64 bit machines.
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
#include <string.h>

#define ISAAC_U32_ELEMENTS 256U
#define ISAAC_U8_ELEMENTS (ISAAC_U32_ELEMENTS * sizeof(uint32_t))
#define ISAAC_SEED_MAX_BYTES ISAAC_U8_ELEMENTS

/**
 * Context of the ISAAC CPRNG.
 *
 * Maps to `randctx` from the original implementation.
 */
typedef struct
{
    uint32_t result[ISAAC_U32_ELEMENTS];
    uint32_t mem[ISAAC_U32_ELEMENTS];
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint16_t next32_index;
    uint16_t next8_index;
} isaac_ctx_t;

/**
 * Initialises the ISAAC CPRNG with a seed.
 *
 * Maps to `void randinit(randctx *r, word flag)` from the original
 * implementation.
 *
 * @warning
 * Failing to provide a seed (NULL or long 0 bytes), will make the whole CSPRNG
 * insecure as a zero-seed is used instead. This is only useful if a
 * **non-cryptographic** PRNG is required.
 *
 * @warning
 * Providing a seed with low entropy will result in the whole CSPRNG to be
 * weak.
 *
 * @param ctx the ISAAC state to be initialised.
 * @param seed pointer to the seed to use, which is copied into the context.
 * - If NULL, then a zero seed is used instead (**insecure!**)
 * @param seed_bytes amount of **bytes** in the seed, max #ISAAC_SEED_MAX_BYTES.
 * - If 0, then a zero seed is used instead (**insecure!**)
 * - If > #ISAAC_SEED_MAX_BYTES, then only #ISAAC_SEED_MAX_BYTES will be used
 * - If < #ISAAC_SEED_MAX_BYTES, then the provided bytes will be used and the
 *   rest will be zero-padded.
 */
void isaac_init(isaac_ctx_t* ctx, const void* seed, uint16_t seed_bytes);

/**
 * Provides the next pseudo-random 32-bit integer.
 *
 * After #ISAAC_U32_ELEMENTS calls it will automatically reshuffle the ISAAC
 * state to provide #ISAAC_U32_ELEMENTS new elements. This means that
 * #ISAAC_U32_ELEMENTS calls are very cheap (just reading the uint32_t value
 * from the state), and the #ISAAC_U32_ELEMENTS+1st call is expensive.
 *
 * @warning
 * **Use either isaac_next32() or isaac_next8(), never both**, especially not
 * in an interleaved manner. The issue is that isaac_next8() reads bytes
 * from the isaac_next32() output; this means that calling isaac_next8() and
 * then isaac_next32() will produce the same byte twice, which is **unsecure**
 * and predictable.
 *
 * @param ctx the ISAAC state, already initialised.
 * @return a pseudo-random 32-bit integer.
 */
uint32_t isaac_next32(isaac_ctx_t* ctx);

/**
 * Provides the next pseudo-random byte.
 *
 * Basically provides the isaac_next32() output byte-by-byte. The order
 * of the bytes is from (uint32_t*)[0] to (uint32_t*)[3].
 *
 * After #ISAAC_U8_ELEMENTS calls it will automatically reshuffle the ISAAC
 * state to provide #ISAAC_U8_ELEMENTS new elements. This means that
 * #ISAAC_U8_ELEMENTS calls are very cheap (just reading the uint8_t value
 * from the state), and the #ISAAC_U8_ELEMENTS+1st call is expensive.
 *
 * @warning
 * **Use either isaac_next32() or isaac_next8(), never both**, especially not
 * in an interleaved manner. The issue is that isaac_next8() reads bytes
 * from the isaac_next32() output; this means that calling isaac_next8() and
 * then isaac_next32() will produce the same byte twice, which is **unsecure**
 * and predictable.
 *
 * @param ctx the ISAAC state, already initialised.
 * @return a pseudo-random byte.
 */
uint8_t isaac_next8(isaac_ctx_t* ctx);


#ifdef __cplusplus
}
#endif

#endif  /* ISAAC_H */
