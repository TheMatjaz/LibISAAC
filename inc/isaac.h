/**
 * @file
 *
 * ISAAC, the fast cryptographic pseudo random number generator (CPRNG), wrapped
 * into a modern, C11, documented API and package. Quoting from its
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
 * This implementation is based on the original `rand.c` and
 * `isaac64.c`, which uses 32-bit and 64-bit words respectively.
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
 * Version of the LibISAAC API using semantic versioning.
 */
#define LIBISAAC_VERSION "1.0.0"

#include <stdint.h>
#include <stddef.h>

#ifndef ISAAC_BITS
    #define ISAAC_BITS 64
#endif
#if (ISAAC_BITS == 32)
typedef uint32_t isaac_uint_t;
#elif (ISAAC_BITS == 64)
typedef uint64_t isaac_uint_t;
#else
_Static_assert(0, "Only 32 or 64 bit words are supported.");
#endif

#define ISAAC_ELEMENTS 256U
#define ISAAC_SEED_MAX_BYTES ISAAC_ELEMENTS

/**
 * Context of the ISAAC CPRNG.
 *
 * Maps to `randctx` from the original implementation.
 */
typedef struct
{
    isaac_uint_t result[ISAAC_ELEMENTS];
    isaac_uint_t mem[ISAAC_ELEMENTS];
    isaac_uint_t a;
    isaac_uint_t b;
    isaac_uint_t c;
    /**
     * Index of the next value to output in the stream.
     *
     * Note: this value could be a uint16_t instead of a isaac_uint_t, but by using
     * a isaac_uint_t we avoid any padding at the end of the struct.
     */
    isaac_uint_t next_index;
} isaac_ctx_t;

/**
 * Initialises the ISAAC CPRNG with a seed.
 *
 * The seed is copied value-wise into the ISAAC state, not byte-wise. That
 * means that a uint8_t array {1,2,3,4} is copied into the ctx->result[]
 * isaac_uint_t array as {1,2,3,4,0,...,0}, where each value is a isaac_uint_t value.
 * Looking at the bytes and assuming little Endian byte order, the result is
 * {1,2,3,4} --> {1,0,0,0,2,0,0,0,3,0,0,0,4,0,0,0,0,...,0}.
 *
 * The reason behind this choice is to avoid issues with endianness; as ISAAC
 * works on isaac_uint_t values rather than their bytes, setting the isaac_uint_t values
 * and not their bytes, shall produce the same CPRNG stream on architectures
 * with different endianness. A isaac_uint_t* could also be a valid choice as seed
 * input, but seeds are usually cryptographic keys and those are byte arrays,
 * so a developer could be confused on how to insert a uint8_t* seed into
 * a isaac_uint_t*.
 *
 * Maps to `void randinit(randctx *r, word flag)` from the original
 * implementation. Equivalent to a true `flag` with a seed provided. The
 * false `flag` is not available, as it should not be used for security
 * purposes.
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
void isaac_init(isaac_ctx_t* ctx, const uint8_t* seed, uint16_t seed_bytes);

/**
 * Provides the next pseudo-random integer.
 *
 * Because ISAAC works on 32 or 64 bit values, the stream is in integers
 * instead of bytes.
 * To convert them to bytes:
 * - get some values into a isaac_uint_t buffer with isaac_stream()
 * - allocate a uint8_t buffer
 * - convert the isaac_uint_t buffer to the uint8_t one using the utility functions
 *   isaac_to_little_endian() or isaac_to_big_endian() for little and big
 *   endian respectively.
 *
 * Every #ISAAC_ELEMENTS values provided it will automatically reshuffle
 * the ISAAC state to cache #ISAAC_ELEMENTS new elements. This means that
 * the first #ISAAC_ELEMENTS values after seeding are very cheap (just
 * copying values from the state) and the #ISAAC_ELEMENTS+1st value is
 * more expensive.
 *
 * @param[in, out] ctx the ISAAC state, already initialised.
 * @param[out] ints pseudo-random integers.
 * @param[in] amount quantity of 32-bit/64-bit integers to generate.
 */
void isaac_stream(isaac_ctx_t* const ctx, isaac_uint_t* ints, size_t amount);

/**
 * Utility function, converting an array of 32-bit/64-bit integers into bytes
 * using **little endian** byte order.
 *
 * Useful to convert a stream of 32-bit/64-bit integers to 8-bit values.
 *
 * @param[out] bytes 8-bit integers. Must be at least \p amount_of_values*4
 * bytes long.
 * @param[in] values 32-bit/64-bit integers, as obtained from isaac_stream()
 * @param[in] amount_of_values quantity of 32-bit/64-bit integers in the
 * \p values buffer.
 */
void isaac_to_little_endian(uint8_t* bytes,
                            const isaac_uint_t* values,
                            size_t amount_of_values);

/**
 * Utility function, converting an array of 32-bit/64-bit integers into bytes
 * using **big endian** byte order.
 *
 * Useful to convert a stream of 32-bit/64-bit integers to 8-bit values.
 *
 * @param[out] bytes 8-bit integers. Must be at least \p amount_of_values*4
 * bytes long.
 * @param[in] values 32-bit/64-bit integers, as obtained from isaac_stream()
 * @param[in] amount_of_values quantity of 32-bit/64-bit integers in the
 * \p values buffer.
 */
void isaac_to_big_endian(uint8_t* bytes,
                         const isaac_uint_t* values,
                         size_t amount_of_values);


#ifdef __cplusplus
}
#endif

#endif  /* ISAAC_H */
