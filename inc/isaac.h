/**
 * @file
 *
 * This library offers the tiny and fast ISAAC cryptographically secure pseudo
 * random number generator (CSPRNG), in its 32-bit and 64-bit version wrapped
 * into a modern, ISO C11, documented API, ready for embedded usage.
 *
 * Use the #ISAAC_BITS macro to compile LibISAAC optimised for 32 or 64 bits.
 * The 32 bit is the classic ISAAC; the 64 bit is ISAAC-64. Note that the output
 * differs between the two and the context grows twice in size when using the 64
 * bit version, but you also get twice the bytes per reshuffling.
 *
 * Then the usage of ISAAC is easy:
 * - init the context with a secret seed with isaac_init()
 * - get any amount of pseudo-random numbers with isaac_stream()
 * - if you need bytes instead of numbers, convert them using the utility
 *   functions isaac_to_big_endian() or isaac_to_little_endian()
 * - When you are done using ISAAC, cleanup the context to avoid leaking secret
 *   data with isaac_cleanup()
 *
 * **About ISAAC**
 *
 * Quoting from its
 * [web page](https://www.burtleburtle.net/bob/rand/isaacafa.html):
 *
 * > ISAAC (Indirection, Shift, Accumulate, Add, and Count) generates 32-bit
 * > random numbers. Averaged out, it requires 18.75 machine cycles to
 * > generate each 32-bit value. Cycles are guaranteed to be at least 240
 * > values long, and they are 28295 values long on average. The results are
 * > uniformly distributed, unbiased, and unpredictable unless you know the
 * > seed.
 * > [...]
 * > ISAAC-64 generates a different sequence than ISAAC, but it uses the same
 * > principles. It uses 64-bit arithmetic. It generates a 64-bit result every
 * > 19 instructions. All cycles are at least 272 values, and the average
 * > cycle length is 216583.
 *
 * ISAAC and its original source code is created by Bob Jenkins and
 * released into the public domain.
 *
 * This implementation is based on the original `rand.c` and
 * `isaac64.c`, which uses 32-bit and 64-bit words respectively.
 *
 * @copyright Copyright © 2020-2021, Matjaž Guštin <dev@matjaz.it>
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

/**
 * @property #ISAAC_BITS
 * Set it to 32 or 64 to optimise ISAAC for 32 or 64 bit words respectively.
 *
 * The 32 bit is the classic ISAAC; the 64 bit is ISAAC-64. Note that the output
 * differs between the two and the context grows twice in size when using the 64
 * bit version, but you also get twice the bytes per reshuffling.
 */
/**
 * @property isaac_uint_t
 * An integer or word used by ISAAC, either a uint32_t or uint64_t.
 */
#ifndef ISAAC_BITS
    #define ISAAC_BITS 64
#endif
#if (ISAAC_BITS == 32)
typedef uint32_t isaac_uint_t;
#elif (ISAAC_BITS == 64)
typedef uint64_t isaac_uint_t;
#else
_Static_assert(0, "ISAAC: only 32 or 64 bit words are supported.");
#endif

/**
 * Amount of elements in ISAAC's context arrays.
 */
#define ISAAC_ELEMENTS 256U

/**
 * Max bytes supported in the seed.
 */
#define ISAAC_SEED_MAX_BYTES ISAAC_ELEMENTS

/**
 * Context of the ISAAC CPRNG.
 *
 * No need to inspect it manually, use the functions instead.
 *
 * Maps to `randctx` from the original implementation.
 */
typedef struct
{
    /**
     * In this field the pseudo-random data is generated.
     */
    isaac_uint_t result[ISAAC_ELEMENTS];
    /** Internal field. */
    isaac_uint_t mem[ISAAC_ELEMENTS];
    /** Internal field. */
    isaac_uint_t a;
    /** Internal field. */
    isaac_uint_t b;
    /** Internal field. */
    isaac_uint_t c;
    /**
     * Index of the next value to output in the stream.
     *
     * Note: this value could be a uint16_t instead of a isaac_uint_t, but by
     * using an isaac_uint_t we avoid any padding at the end of the struct.
     */
    isaac_uint_t stream_index;
} isaac_ctx_t;

/**
 * Initialises the ISAAC CPRNG with a seed.
 *
 * The seed is copied value-wise into the ISAAC state, not byte-wise. That
 * means that a uint8_t array {1,2,3,4} is copied into the ctx->result[]
 * isaac_uint_t array as {1,2,3,4,0,...,0}, where each value is a isaac_uint_t
 * value.
 * Looking at the bytes and assuming little Endian byte order, the result is
 * {1,2,3,4} --> {1,0,0,0,2,0,0,0,3,0,0,0,4,0,0,0,0,...,0}.
 *
 * The reason behind this choice is to avoid issues with endianness; as ISAAC
 * works on isaac_uint_t values rather than their bytes, setting the
 * isaac_uint_t values and not their bytes, shall produce the same CPRNG stream
 * on architectures with different endianness.
 * An isaac_uint_t* could also be a valid choice as seed
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
 * @param[in, out] ctx the ISAAC state to be initialised. Does nothing when
 * NULL.
 * @param[in] seed pointer to the seed to use, which is copied into the context.
 * - If NULL, then a zero seed is used instead (**insecure!**)
 * @param[in] seed_bytes amount of **bytes** in the seed, max
 * #ISAAC_SEED_MAX_BYTES.
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
 * - convert the isaac_uint_t buffer to the uint8_t one using the utility
 *   functions isaac_to_little_endian() or isaac_to_big_endian() for little and
 *   big endian respectively.
 *
 * Every #ISAAC_ELEMENTS values generated it will automatically reshuffle
 * the ISAAC state to cache #ISAAC_ELEMENTS new elements. This means that
 * the first #ISAAC_ELEMENTS values after seeding are very cheap (just
 * copying values from the state) and the #ISAAC_ELEMENTS+1st value is
 * more expensive and so on.
 *
 * @param[in, out] ctx the ISAAC state, already initialised.
 * Does nothing when NULL.
 * @param[out] ints pseudo-random integers. Does nothing when NULL.
 * @param[in] amount quantity of 32-bit/64-bit integers to generate.
 */
void isaac_stream(isaac_ctx_t* ctx, isaac_uint_t* ints, size_t amount);

/**
 * Safely erases the context.
 *
 * Useful to avoid leaking information about the seed or the state after
 * finishing using ISAAC.
 *
 * There is no need to call this function before using isaac_init(), including
 * when re-initing an existing context.
 *
 * @param[in, out] ctx the ISAAC state to cleanup. Does nothing when NULL.
 */
void isaac_cleanup(isaac_ctx_t* ctx);

/**
 * Utility function, converting an array of 32-bit/64-bit integers into bytes
 * using **little endian** byte order.
 *
 * Useful to convert a stream of 32-bit/64-bit integers to 8-bit values.
 *
 * @param[out] bytes 8-bit integers. Must be at least \p amount_of_values*4
 * bytes long. Does nothing when NULL.
 * @param[in] values 32-bit/64-bit integers, as obtained from isaac_stream().
 * Does nothing when NULL.
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
 * bytes long. Does nothing when NULL.
 * @param[in] values 32-bit/64-bit integers, as obtained from isaac_stream().
 * Does nothing when NULL.
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
