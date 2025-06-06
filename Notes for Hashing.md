The notes I have for the hash computation done for the `ASCII_7SEG_NUMS_AND_ERROR_ONLY` variant of this library are present below:

```
E  69	 0100 0101
e  101 0110 0101
R  82	 0101 0010
r  114 0111 0010
O  79	 0100 1111
o  111 0110 1111
```

The `'e'`s have `01` endings   
The `'r'`s have `10` endings   
The `'o'`s have `11` endings   

The difference between lowercase and uppercase for all of them is bit 5

If I map the lowercase of each to indices 0, 2, and 4, and then just use bit 5 to add 1, I get my hash.

```
1 001 → 0 000
2 010 → 2 010
3 011 → 4 100
```

```
f(x) = 2x - 2 = 2(x - 1) = (x - 1) << 1
g(x) = (x & 010) | ( ((x & 011) == 011) << 3 )
```

`f(x)` has less operations.
Then simply `F(x) = f(x) + ((x & 0010 0000) == 0) = ((x - 1) << 1) + ((x & 0x20) == 0)`
That's 5 operations total. Actually, we'll need to AND x /w `0011` first for the left side of the addition, so 6 operations.

We could also modulo 17, and that would work to provide a collision-free hash for this domain of ascii letters, but there's the inefficient space cost and a division operation is expensive on some MCU platforms (e.g., the Infineon XC2287 microcontroller takes up to 19 cycles to perform a division, worst-case).