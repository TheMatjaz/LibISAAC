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


#ifndef min
# define min(a, b) (((a)<(b)) ? (a) : (b))
#endif /* min */
#ifndef max
# define max(a, b) (((a)<(b)) ? (b) : (a))
#endif /* max */
#ifndef align
# define align(a) (((uint32_t)a+(sizeof(void *)-1))&(~(sizeof(void *)-1)))
#endif /* align */
#ifndef abs
# define abs(a) (((a)>0) ? (a) : -(a))
#endif

#define ISAAC_IND(mm, x) ((mm)[(x >> 2U) & (ISAAC_SIZE - 1)])

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

static void isaac_shuffle(isaac_ctx_t* const ctx);

void isaac_init(isaac_ctx_t* const ctx, const bool flag)
{
    uint32_t a, b, c, d, e, f, g, h;
    unsigned int i; /* Fastest integer type */

    ctx->a = ctx->b = ctx->c = 0;
    a = b = c = d = e = f = g = h = GOLDEN_RATIO;

    /* Scramble it */
    for (i = 0; i < 4; i++)
    {
        ISAAC_MIX(a, b, c, d, e, f, g, h);
    }
    /* If (flag==TRUE), then use the contents of result[] to initialize mm[]. */
    if (flag)
    {
        /* Initialise using the contents of result[] as the seed. */
        for (i = 0; i < ISAAC_SIZE; i += 8)
        {
            a += ctx->result[i];
            b += ctx->result[i + 1];
            c += ctx->result[i + 2];
            d += ctx->result[i + 3];
            e += ctx->result[i + 4];
            f += ctx->result[i + 5];
            g += ctx->result[i + 6];
            h += ctx->result[i + 7];
            ISAAC_MIX(a, b, c, d, e, f, g, h);
            ctx->mem[i] = a;
            ctx->mem[i + 1] = b;
            ctx->mem[i + 2] = c;
            ctx->mem[i + 3] = d;
            ctx->mem[i + 4] = e;
            ctx->mem[i + 5] = f;
            ctx->mem[i + 6] = g;
            ctx->mem[i + 7] = h;
        }
        /* Do a second pass to make all of the seed affect all of ctx->mem. */
        for (i = 0; i < ISAAC_SIZE; i += 8)
        {
            a += ctx->mem[i];
            b += ctx->mem[i + 1];
            c += ctx->mem[i + 2];
            d += ctx->mem[i + 3];
            e += ctx->mem[i + 4];
            f += ctx->mem[i + 5];
            g += ctx->mem[i + 6];
            h += ctx->mem[i + 7];
            ISAAC_MIX(a, b, c, d, e, f, g, h);
            ctx->mem[i] = a;
            ctx->mem[i + 1] = b;
            ctx->mem[i + 2] = c;
            ctx->mem[i + 3] = d;
            ctx->mem[i + 4] = e;
            ctx->mem[i + 5] = f;
            ctx->mem[i + 6] = g;
            ctx->mem[i + 7] = h;
        }
    }
    else
    {
        for (i = 0; i < ISAAC_SIZE; i += 8)
        {
            /* Fill in ctx->mem[] with messy stuff. */
            ISAAC_MIX(a, b, c, d, e, f, g, h);
            ctx->mem[i] = a;
            ctx->mem[i + 1] = b;
            ctx->mem[i + 2] = c;
            ctx->mem[i + 3] = d;
            ctx->mem[i + 4] = e;
            ctx->mem[i + 5] = f;
            ctx->mem[i + 6] = g;
            ctx->mem[i + 7] = h;
        }
    }
    /* Fill in the first set of results. */
    isaac_shuffle(ctx);
    /* Prepare to use the first set of results. */
    ctx->available_next_values = ISAAC_SIZE;
}

/*
 * Maps to `void isaac(randctx*)` from the original implementation.
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

    for (m = mm, mend = m2 = m + (ISAAC_SIZE / 2U); m < mend;)
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

uint32_t isaac_next(isaac_ctx_t* const ctx)
{
    if (!(ctx->available_next_values--))
    {
        isaac_shuffle(ctx);
        ctx->available_next_values = ISAAC_SIZE - 1;
    }
    return ctx->result[ctx->available_next_values];
}
