### Hexadecimal
Base 16
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, a (10), b (11), c (12), d (13), e (14), f (15)

A hexadecimal digit represents 4 bits.
Accordingly, ff ff ff in hexadecimal actually signifies 1111 1111 1111 1111 1111 1111 in binary.
00 00 ff = RED

* JPG = 24 bits per pixel (or 3 bytes) *
* 1 byte equals 8 bits *

The first three bytes of JPEGs are:
0xff 0xd8 0xff

The fourth byte, meanwhile, is either:
0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7,
0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, or 0xef.
Put another way, the fourth byte’s first four bits are 1110.

The start of a JPEG usually demarks the end of another.

Digital cameras often initialize cards with a FAT file system whose
"block size" is 512 bytes (B). The implication is that these cameras only write to
those cards in units of 512 B. A photo that’s 1 MB (i.e., 1,048,576 B)
thus takes up 1048576 ÷ 512 = 2048 "blocks" on a memory card.
But so does a photo that’s, say, one byte smaller (i.e., 1,048,575 B)!
The wasted space on disk is called "slack space."
Forensic investigators often look at slack space for remnants of suspicious data.

## RGB
8 bits to signify the amount of red in a pixel’s color
8 bits to signify the amount of green in a pixel’s color
8 bits to signify the amount of blue in a pixel’s color

If the R, G, and B values of some pixel in a BMP are, say,
0xff, 0x00, and 0x00 in hexadecimal, that pixel is purely red,
as 0xff (otherwise known as 255 in decimal) implies "a lot of red,"
while 0x00 and 0x00 imply "no green" and "no blue," respectively.

* A file is just a sequence of bits, arranged in some fashion.*

A 24-bit BMP file is essentially just a sequence of bits,
(almost) every 24 of which happen to represent some pixel’s color.
a BMP file also contains some "metadata," information like an image’s height and width.
That metadata is stored at the beginning of the file in the form of two data structures
generally referred to as "headers":

1. The 1st header, called BITMAPFILEHEADER, is 14 bytes long
2. The 2nd header, called BITMAPINFOHEADER, is 40 bytes long

Immediately following these headers is the actual bitmap:
an array of bytes, triples of which represent a pixel’s color.
BMP stores these triples backwards (i.e., as BGR):
8 bits for blue, followed by 8 bits for green, followed by 8 bits for red.

3. There’s an additional header right after BITMAPINFOHEADER called RGBQUAD,
an array that defines "intensity values" for each of the colors in a device’s palette

smiley.bmp is 8 pixels wide by 8 pixels tall,
it’s a 24-bit BMP (each of whose pixels is represented with 24 ÷ 8 = 3 bytes).
Each row (aka "scanline") thus takes up (8 pixels) × (3 bytes per pixel) = 24 bytes.

small.bmp is (3 pixels) × (3 bytes per pixel) = 9 bytes, which is not a multiple of 4.
And so the scanline is "padded" with as many zeroes as it takes to extend
the scanline’s length to a multiple of 4.

Between 0 and 3 bytes of padding are needed for each scanline in a 24-bit BMP.
In the case of small.bmp, 3 bytes' worth of zeroes are needed,
since (3 pixels) × (3 bytes per pixel) + (3 bytes of padding) = 12 bytes,
which is a multiple of 4.

large.bmp is 12 pixels by 12 pixels,
so (12 pixels) × (3 bytes per pixel) = 36 bytes.
