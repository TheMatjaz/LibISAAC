/**
 * @file
 *
 * Code used to generate the test vectors used in other
 * test files of LibISAAC. It requires the original implementation of ISAAC,
 * that is:
 * - rand.h
 * - standard.h
 * - rand.c or randport.c
 *
 * Compile into an executable and run it.
 *
 * @copyright Copyright © 2020, Matjaž Guštin <dev@matjaz.it>
 * <https://matjaz.it>. All rights reserved.
 * @license BSD 3-clause license.
 */

#include "standard.h"
#include "rand.h"

static void print_ctx(const randctx* const ctx)
{
    printf(".next_index = 0x%08XUL,\n", 0);
    printf(".a = 0x%08XUL,\n", ctx->randa);
    printf(".b = 0x%08XUL,\n", ctx->randb);
    printf(".c = 0x%08XUL,\n", ctx->randc);
    printf(".result = {");
    for (unsigned int i = 0; i < RANDSIZ; i++)
    {
        printf("0x%08XUL, ", ctx->randrsl[i]);
    }
    printf("\n},\n.mem = {");
    for (unsigned int i = 0; i < RANDSIZ; i++)
    {
        printf("0x%08XUL, ", ctx->randmem[i]);
    }
    puts("\n}\n\n");
}

static void ctx_zero_seed(void)
{
    randctx ctx;
    for (unsigned long int i = 0; i < 256; i++)
    {
        ctx.randrsl[i] = 0;  // Zero seed
    }
    randinit(&ctx, 1); // Init ISAAC with zero seed
    puts("Context with zero-initialised seed:");
    print_ctx(&ctx);
}

static void ctx_nonzero_seed(void)
{
    randctx ctx;
    const unsigned char seed[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    unsigned long int i;
    for (i = 0; i < 8; i++)
    {
        ctx.randrsl[i] = seed[i];  // Value-wise copy, not byte-wise
    }
    for (i = 8; i < 256; i++)
    {
        ctx.randrsl[i] = 0;  // Zero padding
    }
    randinit(&ctx, 1);  // Init ISAAC with a non-zero seed
    puts("Context with seed {1,2,3,4,5,6,7,8}:");
    print_ctx(&ctx);
}

static void stream_from_zero_seed(void)
{
    randctx ctx;
    unsigned long int i, j;
    for (i = 0; i < 256; i++)
    {
        ctx.randrsl[i] = 0;  // Zero seed
    }
    randinit(&ctx, 1);  // Init ISAAC with zero seed
    puts("Getting stream of 512 values from zero seed");
    for (j = 0; j < 2; j++)
    {
        for (i = 0; i < 256; i++)
        {
            printf("0x%08XUL, ", ctx.randrsl[i]);
        }
        isaac(&ctx);
    }
    puts("");
}

static void stream_from_nonzero_seed(void)
{
    randctx ctx;
    unsigned long int i, j;
    const unsigned char seed[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    for (i = 0; i < 8; i++)
    {
        ctx.randrsl[i] = seed[i];  // Value-wise copy, not byte-wise
    }
    for (i = 8; i < 256; i++)
    {
        ctx.randrsl[i] = 0;  // Zero padding
    }
    randinit(&ctx, 1);  // Init ISAAC with non-zero seed
    puts("Getting stream of 512 values from non-zero seed");
    for (j = 0; j < 2; j++)
    {
        for (i = 0; i < 256; i++)
        {
            printf("0x%08XUL, ", ctx.randrsl[i]);
        }
        isaac(&ctx);
    }
    puts("");
}

int main(void)
{
    ctx_zero_seed();
    ctx_nonzero_seed();
    stream_from_zero_seed();
    stream_from_nonzero_seed();
    return 0;
}
