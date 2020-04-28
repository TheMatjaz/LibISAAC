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
    printf(".cnt = 0x%08XUL,\n", ctx->randcnt);
    printf(".a = 0x%08XUL,\n", ctx->randa);
    printf(".b = 0x%08XUL,\n", ctx->randb);
    printf(".c = 0x%08XUL,\n", ctx->randc);
    printf(".rsl = {");
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

static void ctx_no_init(void)
{
    randctx ctx;
    randinit(&ctx, 0); // Init ISAAC without a seed
    puts("Context with no seed:");
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

static void next_values_zero_seed(void)
{
    randctx ctx;
    unsigned long int i;
    unsigned long int next;
    for (i = 0; i < 256; i++)
    {
        ctx.randrsl[i] = 0;  // Zero seed
    }
    randinit(&ctx, 1);  // Init ISAAC with zero seed
    puts("Running next() 512 times with zero seed");
    for (i = 0; i < 512; i++)
    {
        next = rand(&ctx);
        printf("0x%08lXUL, ", next);
    }
    puts("");
}

static void next_values_nonzero_seed(void)
{
    randctx ctx;
    unsigned long int i;
    unsigned long int next;
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
    puts("Running next() 512 times with non-zero seed");
    for (i = 0; i < 512; i++)
    {
        next = rand(&ctx);
        printf("0x%08lXUL, ", next);
    }
}

int main(void)
{
    ctx_zero_seed();
    ctx_no_init();
    ctx_nonzero_seed();
    next_values_zero_seed();
    next_values_nonzero_seed();
    return 0;
}
