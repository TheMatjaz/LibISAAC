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

#include "isaac.h"

#define ISAAC_IND(mm, x) ((mm)[(x >> 2U) & (ISAAC_U32_ELEMENTS - 1)])

#define ISAAC_STEP(mix, a, b, mm, m, m2, r, x) \
{ \
  x = *m;  \
  a = ((a^(mix)) + *(m2++)); \
  *(m++) = y = (ISAAC_IND(mm, x) + a + b); \
  *(r++) = b = (ISAAC_IND(mm, y >> 8U) + x) & UINT32_MAX; \
}

#define ISAAC_MIX(a, b, c, d, e, f, g, h) \
{ \
   a ^= b << 11U;                d += a; b += c; \
   b ^= (c & UINT32_MAX) >> 2U;  e += b; c += d; \
   c ^= d << 8U;                 f += c; d += e; \
   d ^= (e & UINT32_MAX) >> 16U; g += d; e += f; \
   e ^= f << 10U;                h += e; f += g; \
   f ^= (g & UINT32_MAX) >> 4U;  a += f; g += h; \
   g ^= h << 8U;                 b += g; h += a; \
   h ^= (a & UINT32_MAX) >> 9U;  c += h; a += b; \
}

/* Explanations why it does not look like 1.618033988749894848...:
 * https://stackoverflow.com/a/4948967
 * https://softwareengineering.stackexchange.com/a/63605
 */
#define GOLDEN_RATIO 0x9e3779b9

static void isaac_shuffle(isaac_ctx_t* ctx);

static void set_seed(isaac_ctx_t* ctx,
                     const uint8_t* seed,
                     uint16_t seed_bytes);

void isaac_init(isaac_ctx_t* const ctx,
                const uint8_t* const seed,
                const uint16_t seed_bytes)
{
    uint32_t a, b, c, d, e, f, g, h;
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
    for (i = 0; i < ISAAC_U32_ELEMENTS; i += 8)
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
    for (i = 0; i < ISAAC_U32_ELEMENTS; i += 8)
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
    ctx->next32_index = ISAAC_U32_ELEMENTS - 1;
    ctx->next8_index = 0;
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
    uint32_t* m;
    uint32_t* mm = ctx->mem;
    uint32_t* m2;
    uint32_t* r = ctx->result;
    uint32_t* mend;
    uint32_t a = ctx->a;
    uint32_t b = ctx->b + (++ctx->c);
    uint32_t x;
    uint32_t y;

    for (m = mm, mend = m2 = m + (ISAAC_U32_ELEMENTS / 2U); m < mend;)
    {
        ISAAC_STEP(a << 13U, a, b, mm, m, m2, r, x);
        ISAAC_STEP((a & UINT32_MAX) >> 6U, a, b, mm, m, m2, r, x);
        ISAAC_STEP(a << 2U, a, b, mm, m, m2, r, x);
        ISAAC_STEP((a & UINT32_MAX) >> 16U, a, b, mm, m, m2, r, x);
    }
    for (m2 = mm; m2 < mend;)
    {
        ISAAC_STEP(a << 13U, a, b, mm, m, m2, r, x);
        ISAAC_STEP((a & UINT32_MAX) >> 6U, a, b, mm, m, m2, r, x);
        ISAAC_STEP(a << 2U, a, b, mm, m, m2, r, x);
        ISAAC_STEP((a & UINT32_MAX) >> 16U, a, b, mm, m, m2, r, x);
    }
    ctx->b = b;
    ctx->a = a;
}

uint32_t isaac_next32(isaac_ctx_t* const ctx)
{
    const uint32_t next32 = ctx->result[ctx->next32_index];
    if (ctx->next32_index == 0)
    {
        /* This is the last value we could extract before the reshuffle. */
        isaac_shuffle(ctx);
        ctx->next32_index = ISAAC_U32_ELEMENTS - 1;
    }
    else
    {
        ctx->next32_index--;
    }
    return next32;
}


uint8_t isaac_next8(isaac_ctx_t* const ctx)
{
    /* We read the same next32 value 4 times and extract 4 different bytes from
     * it, one per next8 call. */
    const uint8_t next8 = (uint8_t) (
            ctx->result[ctx->next32_index] >> ctx->next8_index * 8U
    );
    if (ctx->next8_index >= 3)
    {
        ctx->next8_index = 0;
        isaac_next32(ctx);
    }
    else
    {
        ctx->next8_index++;
    }
    return next8;
}
