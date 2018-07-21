# Questions

## What's `stdint.h`?

TODO
Standard input and output library

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

TODO
To represent different types of data in a strict manner so to not left to complier's interpretation

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

TODO
1 Byte = 1 BYTE
4 Byte = 1 DWORD
4 Byte = 1 LONG
2 BYte = 1 WORD


## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

TODO
BM.

## What's the difference between `bfSize` and `biSize`?

TODO
bfSize is the size of the whole file in bytes, while biSize is the size of the BITMAPINFOHEADER header, which equals 40

## What does it mean if `biHeight` is negative?

TODO
A negative biHeight indicates a top-down DIB where it begins with first line on the top.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

TODO
biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

TODO
That means either (or both of) the input or the output file given in the argument does not exist

## Why is the third argument to `fread` always `1` in our code?

TODO
Because the read size is the entire length of the BITMAPFILEHEADER, is it able to read it in one go.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

TODO
2

## What does `fseek` do?

TODO
Skip over padding

## What is `SEEK_CUR`?

TODO
It means use the current location as referecen in moving the file pointer