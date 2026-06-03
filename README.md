Going down memory lane - For my own reference and the general public, recreating the prodecure I deviced in *2013* to generate and use 16, 24, and 32 bit high fonts for the Seeed SSD1308 based OLED display. 
Filling in the repo as I dig up how I did it.

All three of these fonts feature an abbreviated ASCII character set so they will fit in an Anduino Uno.

Steps (incomplete):

1) For the 32 bit font, I created a GIMP image 32 pixels high, by number of chars X 20 pixels wide, with each of the capital ASCII characters plus space and ":" in a 20-pixel wide cell starting at the left. Since the font is mono-spaced, they were just typed in, 0123456789....etc. So each of the characters are 20 bits wide.

NOTE: Make sure all of the chars fit in their cells. Some characters like R, W, Y are problematic.

3) I exported the image as a PGM ASCII format file. PGM has the following format: Two lines of metadata, a third line with the number of cols and number of rows (“128 64”) and successive lines that are rowwise byte by byte pixels in the image. The lines will be either 255 (white) or 0 (black). The head of the file looks like this:
```P2
# CREATOR: The GIMP's PNM Filter Version 1.0
900 32
255
255
etc...
```

4) The PGM file was converted to a C array-of-arrays-of-arrays with pgmtofont.py (in this repo). Since the font is mono-spaced, character boundaries in the width dimension fall every 20 pixels. The script converts the PGM file, which is a row-wise bit for bit sequence of 8 bit pixels 32 rows high, into an [nchars][4][20] array of unsigned chars. We have to read the rowwise data and convert it into the “pages” the OLED controller wants. There are 8 pages, with 128 bytes in each page. Each byte is a single column “stack” 8 bits high. (See the data sheet.) 
