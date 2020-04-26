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

#define ISAAC_LEFTSHIFT 8U

#define ISAAC_IND(mm, x) ((mm)[(x >> 2U) & (ISAAC_SIZE - 1)])

#define ISAAC_STEP(mix, a, b, mm, m, m2, r, x) \
{ \
  x = *m;  \
  a = ((a^(mix)) + *(m2++)); \
  *(m++) = y = (ISAAC_IND(mm, x) + a + b); \
  *(r++) = b = (ISAAC_IND(mm, y >> ISAAC_LEFTSHIFT) + x) & UINT32_MAX; \
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

static void isaac_round(isaac_ctx_t* ctx);

void isaac_init(isaac_ctx_t* const ctx, const bool flag)
{
    uint32_t* m;
    uint32_t* r;
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;
    uint32_t e;
    uint32_t f;
    uint32_t g;
    uint32_t h;
    unsigned int i; /* Fastest integer type */

    ctx->a = ctx->b = ctx->c = 0;
    m = ctx->mem;
    r = ctx->rsl;
    a = b = c = d = e = f = g = h = GOLDEN_RATIO;

    /* scramble it */
    for (i = 0; i < 4; i++)
    {
        ISAAC_MIX(a, b, c, d, e, f, g, h);
    }
    /* if (flag==TRUE), then use the contents of rsl[] to initialize mm[]. */
    if (flag)
    {
        /* initialize using the contents of r[] as the seed */
        for (i = 0; i < ISAAC_SIZE; i += 8)
        {
            a += r[i];
            b += r[i + 1];
            c += r[i + 2];
            d += r[i + 3];
            e += r[i + 4];
            f += r[i + 5];
            g += r[i + 6];
            h += r[i + 7];
            ISAAC_MIX(a, b, c, d, e, f, g, h);
            m[i] = a;
            m[i + 1] = b;
            m[i + 2] = c;
            m[i + 3] = d;
            m[i + 4] = e;
            m[i + 5] = f;
            m[i + 6] = g;
            m[i + 7] = h;
        }
        /* do a second pass to make all of the seed affect all of m */
        for (i = 0; i < ISAAC_SIZE; i += 8)
        {
            a += m[i];
            b += m[i + 1];
            c += m[i + 2];
            d += m[i + 3];
            e += m[i + 4];
            f += m[i + 5];
            g += m[i + 6];
            h += m[i + 7];
            ISAAC_MIX(a, b, c, d, e, f, g, h);
            m[i] = a;
            m[i + 1] = b;
            m[i + 2] = c;
            m[i + 3] = d;
            m[i + 4] = e;
            m[i + 5] = f;
            m[i + 6] = g;
            m[i + 7] = h;
        }
    }
    else
    {
        for (i = 0; i < ISAAC_SIZE; i += 8)
        {
            /* fill in mm[] with messy stuff */
            ISAAC_MIX(a, b, c, d, e, f, g, h);
            m[i] = a;
            m[i + 1] = b;
            m[i + 2] = c;
            m[i + 3] = d;
            m[i + 4] = e;
            m[i + 5] = f;
            m[i + 6] = g;
            m[i + 7] = h;
        }
    }
    /* fill in the first set of results */
    isaac_round(ctx);
    /* prepare to use the first set of results */
    ctx->cnt = ISAAC_SIZE;
}

/*
 * Maps to `void isaac(randctx*)` from the original implementation.
 */
static void isaac_round(isaac_ctx_t* const ctx)
{
    uint32_t* m;
    uint32_t* mm;
    uint32_t* m2;
    uint32_t* r;
    uint32_t* mend;
    uint32_t a;
    uint32_t b;
    uint32_t x;
    uint32_t y;

    mm = ctx->mem;
    r = ctx->rsl;
    a = ctx->a;
    b = ctx->b + (++ctx->c);
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
    if (!(ctx->cnt--))
    {
        isaac_round(ctx);
        ctx->cnt = ISAAC_SIZE - 1;
    }
    return ctx->rsl[ctx->cnt];
}

#ifdef NEVER
int main()
{

}
#endif
