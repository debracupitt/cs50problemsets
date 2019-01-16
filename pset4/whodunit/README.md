# Questions

## What's `stdint.h`?

The stdint.h is a header file in the C standard library and it's also known as the C99 standard.
It defines new integer types - with them, you can be more specific in what you want from your integer.
For example, you can use fixed-width integer type int32_t,
which is guaranteed to have 32 bits anywhere.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

These terms are useful for cross-platform implementation of a standard data size.
It’s easier to have aliases for explicit fixed width integers that set the number of bytes,
because one system an int might be a long in another.
For example, uint24_t means an integer that is exactly 24 bits wide.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE: 1
DWORD: 4
LONG: 4
WORD: 2

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be?
## Leading bytes used to identify file formats (with high probability) are generally called
## "magic numbers."

The first 2 bytes of the BMP file format are the character "B" then the character "M" in ASCII encoding.

ASCII:  B = 66
        M = 77
Hex:    0x424d

## What's the difference between `bfSize` and `biSize`?

bfSize is the size of, in bytes, of the bitmap file. (BITMAPFILEHEADER)
biSize is the number of bytes required by the structure. (BITMAPINFOHEADER)

## What does it mean if `biHeight` is negative?

If biHeight is negative, the bitmap is a top-down DIB and its origin is the upper-left corner.
If biHeight is negative, indicating a top-down DIB, biCompression must be either BI_RGB or BI_BITFIELDS.
Top-down DIBs cannot be compressed.
If biCompression is BI_JPEG or BI_PNG,
the biHeight member specifies the height of the decompressed JPEG or PNG image file, respectively.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

If there is no file at the memory address FILE *inptr.

## Why is the third argument to `fread` always `1` in our code?

fread's third argument is always 1 because we are iterating over every
pixel in the image - it meets the purposes of our program.

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

If bi.biWidth = 3, padding = 3
int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4 = 3

## What does `fseek` do?

fseek sets the file position of the stream to the given offset.

## What is `SEEK_CUR`?

SEEK_CUR is the current position of the file pointer

## Whodunit?

It was Professor Plum with the candlestick in the library.
