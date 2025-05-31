# ASCII to 7-Segment Library `libascii7seg` :capital_abcd: :1234:
This library provides a small API to encode a range of supported ASCII characters into the individual segment values that the downstream can then use to drive a [7-segment display](https://en.wikipedia.org/wiki/Seven-segment_display). This can be used in pretty much any environment and is written conforming to C99.  

See [`ascii7seg.h`](./inc/ascii7seg.h) for the types and API, but to repeat them briefly here, the primary type you'll work with is `Ascii7Seg_Encoding_U` (a union type), which will give you the individual segment values or the entire encoding as a single variable (hence the union type), and the following API is available to you (you pass in the union object, the functions return a pass/fail):   

```c
bool Ascii7Seg_ConvertChar( char ascii_char, union Ascii7Seg_Encoding_U * buf );

bool Ascii7Seg_ConvertWord( const char * str,
                            size_t str_len,
                            union Ascii7Seg_Encoding_U * buf );

bool Ascii7Seg_IsSupportedChar( char ascii_char );
```

### Range of Characters Supported
The macros present within [`ascii7seg_config.h`](./ascii7seg_config.h) allow you to configure which of the following 3 ranges you want this library to support (at compile time). The smaller the range, the better the speed and space performance. By default, the maximum range is what is supported if you choose to do nothing in `ascii7seg_config.h`.   

1. Numerical Digits Only: `0` to `9`
2. Numerical Digits + `"Error"` (both capital and lowercase)
3. Full Range:
   - `0 - 9`
   - `A - Z` and `a - z`
   - Symbols: `[ ] _ - | =`

### Compile-Time Configuration
In addition, the internal implementation of the encoding is _optionally_ configurable (at compile-time), using the macros present within [`ascii7seg_config.h`](./ascii7seg_config.h). Specifically, you can change
- the range of supported characters,
- whether a lookup table is used or a computation (speed vs space) - see benchmark/profiling section,
- and how you want the encoding available to you within `Ascii7Seg_Encoding_U` (bit-packed or separate `bool`'s)

You'd simply set the macros as you like and then rebuild the library for your architecture. The idea behind this flexibility is to allow you, the user, to prioritize speed vs space. Again, this is _optional_ and by default, speed is prioritized (lookup tables are used and the encoding is _not_ bit-packed) for the full range of conceivable ASCII characters on a 7-segment display.

## Usage
In the near future, I will place the various build artifacts produced here into a package and publish that to some package management system that you can then conveniently pull in, but for now, you may:
1. **Download** the static library file for your target in the [**Releases**](https://github.com/memphis242/ascii7seg/releases) page of this repository. I try to include as many possible target environments as I can there, but this is not exhaustive.

2. **Build the Static Library Yourself**: Clone this repo and run `make lib` if you are building for a desktop environment or `make libmcu` to build for an MCU target (you'll need to configure [`mcu_opts.mk`](./mcu_opts.mk)).
   - Presently, only ARM-based MCUs are supported, but you may also just copy the necessary files into your own build environment and build away :building_construction:.
   - You'll need GCC to build for a desktop environment and the [Arm GNU Toolchain](https://developer.arm.com/Tools%20and%20Software/GNU%20Toolchain) to build for the ARM MCU targets.
   - Make
   - Additionally, to utilize the full build process I am using, you'll need:
      - Python3
      - cppcheck

3. **Copy the Necessary Files / Git Submodule**: You'll want `ascii7seg.c`, `ascii7seg.h`, and `ascii7seg_config.h` (modified to your needs if desired). See the [`ascii7seg_config.h`](./ascii7seg_config.h) for details on the configuration supported.

## Profiling & Benchmarking Space + Speed
TODO

## Code Quality
Please see the [`CODING_PRINCIPLES.md`](./CODING_PRINCIPLES.md) file for my philosophy and the software engineering principles/practices that help me produce what I see as quality code.

# Acknowledgements
1. I would like to give a shoutout to @dmadison for the very useful images that he provided in [`dmadison/LED-Segment-ASCII`](https://github.com/dmadison/LED-Segment-ASCII/tree/master). I specifically borrowed [`Segment-Labels.png`](https://github.com/dmadison/LED-Segment-ASCII/blob/497bffc094c866caa2cb729c33de9450d517ba22/Images/Segment-Labels.png) and [`7-Segment - All Supported Chars.png`](https://github.com/dmadison/LED-Segment-ASCII/blob/497bffc094c866caa2cb729c33de9450d517ba22/Images/All%20Characters/7-Segment-ASCII-All.png).

2. Shoutout as well to the [Linux Handbook](https://linuxhandbook.com/ascii-table). I borrowed their image of the ASCII table: [`ASCII Table - The Linux Handbook.png`](./ASCII%20Table%20-%20The%20Linux%20Handbook.png).

