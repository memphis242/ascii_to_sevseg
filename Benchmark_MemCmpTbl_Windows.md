# Memory Usage Comparison

## Memory Section Sizes (Ascending Order of Total Size)

| Configuration | Text | Data | BSS | Total |
|--------------|-----:|-----:|----:|------:|
| wx86-64-nums-bp | 2624 | 0 | 96 | 2720 |
| wx86-64-nums | 2756 | 0 | 96 | 2852 |
| wx86-64-numerr-bp | 3108 | 0 | 96 | 3204 |
| wx86-64-full-bp | 3200 | 0 | 96 | 3296 |
| wx86-64-numerr | 3268 | 0 | 96 | 3364 |
| wx86-64-full-bp-nolut | 3248 | 0 | 128 | 3376 |
| wx86-64-defaults | 3632 | 0 | 96 | 3728 |
| wx86-64-full | 3632 | 0 | 96 | 3728 |
| wx86-64-full-nolut | 3664 | 0 | 128 | 3792 |
| wx86-64-nums-bp-nolut | 4400 | 0 | 160 | 4560 |
| wx86-64-nums-nolut | 4432 | 0 | 160 | 4592 |
| wx86-64-numerr-bp-nolut | 4496 | 0 | 192 | 4688 |
| wx86-64-numerr-nolut | 4512 | 0 | 192 | 4704 |

## Symbol Sizes (Same Order as Above)

| Configuration | Ascii7Seg_ConvertChar | Ascii7Seg_ConvertChar.part.0 | Ascii7Seg_ConvertNum | Ascii7Seg_ConvertWord | Ascii7Seg_IsSupportedChar | ErrorLUT.0 | MasterLUT | NumLUT | PowersOf10 |
|--------------|-----:|-----:|-----:|-----:|-----:|-----:|-----:|-----:|-----:|
| wx86-64-nums-bp | 2192 | - | 1040 | 608 | 176 | - | - | 64 | 160 |
| wx86-64-nums | 2288 | - | 1072 | 640 | 176 | - | - | 96 | 160 |
| wx86-64-numerr-bp | 2640 | - | 1072 | 560 | 368 | 32 | - | 64 | 160 |
| wx86-64-full-bp | 2320 | - | 912 | 416 | 432 | - | 512 | - | 160 |
| wx86-64-numerr | 2736 | - | 1088 | 592 | 368 | 64 | - | 96 | 160 |
| wx86-64-full-bp-nolut | 2496 | - | 1088 | 416 | 432 | - | 544 | - | - |
| wx86-64-defaults | 2368 | - | 928 | 432 | 432 | - | 896 | - | 160 |
| wx86-64-full | 2368 | - | 928 | 432 | 432 | - | 896 | - | 160 |
| wx86-64-full-nolut | 2528 | - | 1088 | 432 | 432 | - | 928 | - | - |
| wx86-64-nums-bp-nolut | 4160 | - | 944 | 1632 | 176 | - | - | - | - |
| wx86-64-nums-nolut | 4192 | - | 960 | 1648 | 176 | - | - | - | - |
| wx86-64-numerr-bp-nolut | 496 | 4240 | 1072 | 416 | 368 | - | - | - | - |
| wx86-64-numerr-nolut | 496 | 4256 | 1072 | 416 | 368 | - | - | - | - |
