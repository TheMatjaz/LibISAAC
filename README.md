ISAAC, the fast CSPRNG, reimplemented in a nicer, documented, modern C11 API
===============================================================================

LibISAAC offers the tiny and fast
[ISAAC](https://www.burtleburtle.net/bob/rand/isaacafa.html) cryptographically
secure pseudo random number generator (CSPRNG), in its 32-bit and 64-bit version
wrapped into a modern, ISO C11, documented API, ready for embedded usage.



About ISAAC
----------------------------------------

Quoting from [its website](https://www.burtleburtle.net/bob/rand/isaacafa.html):

> ISAAC (Indirection, Shift, Accumulate, Add, and Count) generates 32-bit
> random numbers. Averaged out, it requires 18.75 machine cycles to
> generate each 32-bit value. Cycles are guaranteed to be at least 240
> values long, and they are 28295 values long on average. The results are
> uniformly distributed, unbiased, and unpredictable unless you know the
> seed.
> [...]
> ISAAC-64 generates a different sequence than ISAAC, but it uses the same
> principles. It uses 64-bit arithmetic. It generates a 64-bit result every
> 19 instructions. All cycles are at least 272 values, and the average
> cycle length is 216583.

ISAAC and its original source code (on which this version is based on)
were created by Bob Jenkins and released into the public domain.



Usage example
----------------------------------------

```c
// Init the context with a secret seed
isaac_ctx_t ctx;
const uint8_t seed[16] = {1, 2, 3, 4, 5, 6, 7, 8,
                          9, 10, 11, 12, 13, 14, 15, 16};
isaac_init(&ctx, seed, sizeof(seed));

// If you DON'T need ISAAC for security purposes, an all-zero
// seed may also be of interested. Just pass a NULL seed.
isaac_init(&ctx, NULL, 0);

// Extract ANY amount of pseudo-random integers
isaac_uint_t stream[300] = {0};
isaac_stream(&ctx, stream, 300);
isaac_uint_t another_stream[5000] = {0};
isaac_stream(&ctx, stream, 5000);

// Note that ISAAC provides integers, not bytes.
// If you need bytes, convert the integers to little endian-
// or big endian-encoded stream of bytes.
uint8_t bytes[300 * sizeof(isaac_uint_t)];
isaac_to_big_endian(bytes, stream, 300);
// or isaac_to_little_endian(bytes, stream, 300);

// Done using ISAAC? Cleanup the context to avoid leaving traces
// of the state and of the seed.
isaac_cleanup(&ctx);
```



Include it in your project
----------------------------------------

### Bitness

Depending on your architecture, you may want to use the version of ISAAC
optimised for 32 or 64 bit words. To do so, set the `#define ISAAC_BITS`
to `32` or `64` during compilation or directly in the header file. It defaults
to 64 when unspecified.

Differences:
- the output differs between the two (it's expected to differ)
- the context grows twice in size when using the 64 bit version
  - 32 bit: 2064 B
  - 64 bit: 4128 B
- in the 64 bit version, twice the amount of bytes is provided per reshuffling
  of the state

Please note that altering `ISAAC_BITS` does not set your compiler to
compile LibISAAC for a 32 or 64 target architecture, it simply chooses which
integers to use based on **your** choice, not the compiler's. You may want to
choose the best version for your system, but you can compile both versions on
any system.

Examples:

- a 32-bit microcontroller works best with `ISAAC_BITS=32`
- a 64-bit desktop works best with `ISAAC_BITS=64`
- a 64-bit desktop that has to test the output of ISAAC coming from a 32-bit
  microcontroller (assuming the same seed is known to both), should compile with
  `ISAAC=BITS=32` to get the same output.


### Static source inclusion

Copy the `inc/isaac.h` and `src/isaac.c` files into your existing
C project, add them to the source folders and compile..

If you prefer a specific bitness, redefine `ISAAC_BITS` in the header file.


### Compiling into all possible targets

```
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DISAAC_BITS=32
cmake --build .
```

This will build all targets:

- a `libisaac32.a` static library
- a test runner executable `testisaac32`
- the Doxygen documentation (if Doxygen is installed)

To compile with the optimisation for size, use the
`-DCMAKE_BUILD_TYPE=MinSizeRel` flag instead.

If you prefer using 64 bit integers, set `-DISAAC_BITS=64`.
