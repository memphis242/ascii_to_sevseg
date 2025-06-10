# Memory Usage Comparison

## Memory Section Sizes in Bytes (Ascending Order of Total Size)

| Configuration | Text | Data | BSS | Total |
|--------------|-----:|-----:|----:|------:|
| arm-m0plus-nums-bp | 652 | 0 | 0 | 652 |
| arm-m0plus-numerr-bp | 844 | 0 | 0 | 844 |
| arm-m0plus-nums | 876 | 0 | 0 | 876 |
| arm-m0plus-nums-nolut | 984 | 0 | 0 | 984 |
| arm-m0plus-full-bp-nolut | 1024 | 0 | 0 | 1024 |
| arm-m0plus-numerr | 1108 | 0 | 0 | 1108 |
| arm-m0plus-nums-bp-nolut | 1108 | 0 | 0 | 1108 |
| arm-m0plus-full-bp | 1120 | 0 | 0 | 1120 |
| arm-m0plus-numerr-nolut | 1584 | 0 | 0 | 1584 |
| arm-m0plus-numerr-bp-nolut | 1768 | 0 | 0 | 1768 |
| arm-m0plus-full-nolut | 2552 | 0 | 0 | 2552 |
| arm-m0plus-defaults | 2676 | 0 | 0 | 2676 |
| arm-m0plus-full | 2676 | 0 | 0 | 2676 |

## Symbol Sizes in Bytes (Same Order as Above)

| Configuration | Ascii7Seg_ConvertChar | Ascii7Seg_ConvertChar.part.0 | Ascii7Seg_ConvertNum | Ascii7Seg_ConvertWord | Ascii7Seg_IsSupportedChar | ErrorLUT.0 | MasterLUT | NumLUT | PowersOf10 |
|--------------|-----:|-----:|-----:|-----:|-----:|-----:|-----:|-----:|-----:|
| arm-m0plus-nums-bp | 48 | - | 336 | 76 | 24 | - | - | 12 | 152 |
| arm-m0plus-numerr-bp | 112 | - | 336 | 160 | 60 | 6 | - | 12 | 152 |
| arm-m0plus-nums | 68 | - | 424 | 120 | 24 | - | - | 84 | 152 |
| arm-m0plus-nums-nolut | 224 | - | 434 | 300 | 24 | - | - | - | - |
| arm-m0plus-full-bp-nolut | 96 | - | 468 | 136 | 68 | - | 256 | - | - |
| arm-m0plus-numerr | 148 | - | 432 | 188 | 60 | 42 | - | 84 | 152 |
| arm-m0plus-nums-bp-nolut | 272 | - | 408 | 404 | 24 | - | - | - | - |
| arm-m0plus-full-bp | 96 | - | 412 | 136 | 68 | - | 256 | - | 152 |
| arm-m0plus-numerr-nolut | 372 | 332 | 428 | 392 | 60 | - | - | - | - |
| arm-m0plus-numerr-bp-nolut | 424 | 388 | 396 | 500 | 60 | - | - | - | - |
| arm-m0plus-full-nolut | 108 | - | 432 | 152 | 68 | - | 1792 | - | - |
| arm-m0plus-defaults | 108 | - | 404 | 152 | 68 | - | 1792 | - | 152 |
| arm-m0plus-full | 108 | - | 404 | 152 | 68 | - | 1792 | - | 152 |
