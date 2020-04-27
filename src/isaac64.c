/**
 * @file
 *
 * LibISAAC implementation.
 *
 * Basic on the 32-bit portable implementation by Bob Jenkins, originally
 * public domain:
 * https://www.burtleburtle.net/bob/c/randport.c
 *
 * @copyright Copyright © 2020, Matjaž Guštin <dev@matjaz.it>
 * <https://matjaz.it>. All rights reserved.
 * @license BSD 3-clause license.
 */

#include "isaac64.h"

#define ISAAC_IND(mm, x)  (*(uint64_t*)((uint8_t*)(mm) \
                          + ((x) & ((ISAAC_ELEMENTS - 1) << 3))))

#define ISAAC_STEP(mix, a, b, mm, m, m2, r, x) \
{ \
  x = *m;  \
  a = (mix) + *(m2++); \
  *(m++) = y = ISAAC_IND(mm, x) + a + b; \
  *(r++) = b = ISAAC_IND(mm, y >> 8U) + x; \
}

#define ISAAC_MIX(a, b, c, d, e, f, g, h) \
{ \
   a -= e; f ^= h >> 9U;  h += a; \
   b -= f; g ^= a << 9U;  a += b; \
   c -= g; h ^= b >> 23U; b += c; \
   d -= h; a ^= c << 15U; c += d; \
   e -= a; b ^= d >> 14U; d += e; \
   f -= b; c ^= e << 20U; e += f; \
   g -= c; d ^= f >> 17U; f += g; \
   h -= d; e ^= g << 14U; g += h; \
}

/* Explanations why it does not look like 1.618033988749894848...:
 * https://stackoverflow.com/a/4948967
 * https://softwareengineering.stackexchange.com/a/63605
 */
#define GOLDEN_RATIO 0x9e3779b97f4a7c13LL

static void isaac_shuffle(isaac_ctx_t* ctx);

static void set_seed(isaac_ctx_t* ctx,
                     const uint8_t* seed,
                     uint16_t seed_bytes);

void isaac_init(isaac_ctx_t* const ctx,
                const uint8_t* const seed,
                const uint16_t seed_bytes)
{
    if (ctx == NULL)
    {
        return;
    }
    uint64_t a, b, c, d, e, f, g, h;
    uint_fast16_t i; /* Fastest index over elements in result[] and mem[]. */
    ctx->a = ctx->b = ctx->c = 0;
    a = b = c = d = e = f = g = h = GOLDEN_RATIO;
    /* Scramble it */
    for (i = 0; i < 4; i++)
    {
        ISAAC_MIX(a, b, c, d, e, f, g, h);
    }
    set_seed(ctx, seed, seed_bytes);
    /* Initialise using the contents of result[] as the seed. */
    for (i = 0; i < ISAAC_ELEMENTS; i += 8)
    {
        a += ctx->result[i + 0];
        b += ctx->result[i + 1];
        c += ctx->result[i + 2];
        d += ctx->result[i + 3];
        e += ctx->result[i + 4];
        f += ctx->result[i + 5];
        g += ctx->result[i + 6];
        h += ctx->result[i + 7];
        ISAAC_MIX(a, b, c, d, e, f, g, h);
        ctx->mem[i + 0] = a;
        ctx->mem[i + 1] = b;
        ctx->mem[i + 2] = c;
        ctx->mem[i + 3] = d;
        ctx->mem[i + 4] = e;
        ctx->mem[i + 5] = f;
        ctx->mem[i + 6] = g;
        ctx->mem[i + 7] = h;
    }
    /* Do a second pass to make all of the seed affect all of ctx->mem. */
    for (i = 0; i < ISAAC_ELEMENTS; i += 8)
    {
        a += ctx->mem[i + 0];
        b += ctx->mem[i + 1];
        c += ctx->mem[i + 2];
        d += ctx->mem[i + 3];
        e += ctx->mem[i + 4];
        f += ctx->mem[i + 5];
        g += ctx->mem[i + 6];
        h += ctx->mem[i + 7];
        ISAAC_MIX(a, b, c, d, e, f, g, h);
        ctx->mem[i + 0] = a;
        ctx->mem[i + 1] = b;
        ctx->mem[i + 2] = c;
        ctx->mem[i + 3] = d;
        ctx->mem[i + 4] = e;
        ctx->mem[i + 5] = f;
        ctx->mem[i + 6] = g;
        ctx->mem[i + 7] = h;
    }
    /* Fill in the first set of results. */
    isaac_shuffle(ctx);
    /* Prepare to use the first set of results with next32() and next8(). */
    ctx->next64_index = ISAAC_ELEMENTS - 1;
}

/**
 * @internal
 * Copies the seed into ctx->result[], padding it with zeros.
 *
 * @param ctx the ISAAC state
 * @param seed bytes of the seed. If NULL, a zero-seed is used.
 * @param seed_bytes amount of bytes in the seed.
 */
static void set_seed(isaac_ctx_t* const ctx,
                     const uint8_t* const seed,
                     uint16_t seed_bytes)
{
    uint_fast16_t i;
    if (seed != NULL)
    {
        if (seed_bytes > ISAAC_SEED_MAX_BYTES)
        {
            seed_bytes = ISAAC_SEED_MAX_BYTES;
        }
        for (i = 0; i < seed_bytes; i++)
        {
            /* The copy is performed VALUE-wise, not byte wise.
             * By doing so we have same result[] on architectures with different
             * endianness. */
            ctx->result[i] = seed[i];
        }
    }
    else
    {
        seed_bytes = 0;
    }
    for (i = seed_bytes; i < ISAAC_SEED_MAX_BYTES; i++)
    {
        ctx->result[i] = 0;
    }
}

/**
 * @internal
 * Permutes the ISAAC state.
 *
 * Maps to `void isaac(randctx*)` from the original implementation.
 *
 * @param ctx the ISAAC state
 */
static void isaac_shuffle(isaac_ctx_t* const ctx)
{
    uint64_t* m;
    uint64_t* mm = ctx->mem;
    uint64_t* m2;
    uint64_t* r = ctx->result;
    uint64_t* mend;
    uint64_t a = ctx->a;
    uint64_t b = ctx->b + (++ctx->c);
    uint64_t x;
    uint64_t y;

    for (m = mm, mend = m2 = m + (ISAAC_ELEMENTS / 2U); m < mend;)
    {
        ISAAC_STEP(~(a ^ (a << 21U)), a, b, mm, m, m2, r, x);
        ISAAC_STEP(a ^ (a >> 5U), a, b, mm, m, m2, r, x);
        ISAAC_STEP(a ^ (a << 12U), a, b, mm, m, m2, r, x);
        ISAAC_STEP(a ^ (a >> 33U), a, b, mm, m, m2, r, x);
    }
    for (m2 = mm; m2 < mend;)
    {
        ISAAC_STEP(~(a ^ (a << 21U)), a, b, mm, m, m2, r, x);
        ISAAC_STEP(a ^ (a >> 5U), a, b, mm, m, m2, r, x);
        ISAAC_STEP(a ^ (a << 12U), a, b, mm, m, m2, r, x);
        ISAAC_STEP(a ^ (a >> 33U), a, b, mm, m, m2, r, x);
    }
    ctx->b = b;
    ctx->a = a;
}

#define isaac_min(a, b) ((a) < (b)) ? (a) : (b)

void isaac_stream(isaac_ctx_t* const ctx, uint64_t* ints, size_t amount)
{
    if (ctx == NULL || ints == NULL)
    {
        return;
    }
    do
    {
        const size_t available = isaac_min(ctx->next_index + 1, amount);
        for (uint_fast16_t i = 0; i < available; i++)
        {
            *ints++ = ctx->result[ctx->next_index--];
        }
        amount -= available;
        if (ctx->next_index >= ISAAC_ELEMENTS)
        {
            /* next_index underflow, thus out of elements. Reshuffling
             * and preparing new batch of elements. */
            isaac_shuffle(ctx);
            ctx->next_index = ISAAC_ELEMENTS - 1;
        }
    }
    while (amount);
}

void isaac_to_little_endian(uint8_t* bytes,
                            const uint64_t* values,
                            size_t amount_of_values)
{
    if (bytes == NULL || values == NULL)
    {
        return;
    }
    {
        while (amount_of_values--)
        {
            *bytes++ = (uint8_t) (*values);
            *bytes++ = (uint8_t) (*values >> 8U);
            *bytes++ = (uint8_t) (*values >> 16U);
            *bytes++ = (uint8_t) (*values >> 24U);
            *bytes++ = (uint8_t) (*values >> 32U);
            *bytes++ = (uint8_t) (*values >> 40U);
            *bytes++ = (uint8_t) (*values >> 48U);
            *bytes++ = (uint8_t) (*values++ >> 56U);
        }
    }
}

void isaac_to_big_endian(uint8_t* bytes,
                         const uint64_t* values,
                         size_t amount_of_values)
{
    if (bytes == NULL || values == NULL)
    {
        return;
    }
    while (amount_of_values--)
    {
        *bytes++ = (uint8_t) (*values >> 56U);
        *bytes++ = (uint8_t) (*values >> 48U);
        *bytes++ = (uint8_t) (*values >> 40U);
        *bytes++ = (uint8_t) (*values >> 32U);
        *bytes++ = (uint8_t) (*values >> 24U);
        *bytes++ = (uint8_t) (*values >> 16U);
        *bytes++ = (uint8_t) (*values >> 8U);
        *bytes++ = (uint8_t) (*values++);
    }
}
