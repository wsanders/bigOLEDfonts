Going down memory lane - For my own reference and the general public, recreating the prodecure I deviced in *2013* to generate and use 16, 24, and 32 bit high fonts for the Seeed SSD1308 based OLED display. 
Filling in the repo as I dig up how I did it.

All three of these fonts feature an abbreviated ASCII character set so they will fit in an Anduino Uno.

Steps (incomplete):

1) For the 32 bit font, I created a GIMP image 32 pixels high, by number of chars X 20 pixels wide, with each of the ASCII characters in a 20-pixel wide cell starting at the left. Since the font is mono-spaced, they were just typed in, 0123456789....etc. So each of the characters are 20 bits wide.

2) I exported the image as a PGM ASCII format file/ PGM has the following format: Two lines of metadata, a third line with the number of cols and number of rows (“128 64”) and successive lines that are rowwise byte by byte pixels in the image. The lines will be either 255 (white) or 0 (black). The head of the file looks like this:
```P2
# CREATOR: The GIMP's PNM Filter Version 1.0
900 32
255
255
etc...
```

4) The PGM file was converted to a C array-of-arrays-of-arrays with pgmtofont.p (in this repo). Since the font is mono-spaced, character boundaries in the width dimension fall every 20 pixels. The script converts the PGM file, which is a row-wise bit for bit sequence of 8 bit pixels 32 rows high, into an [nchars][4][20] array of unsigned chars. We have to read the rowwise data and convert it into the “pages” the OLED controller wants. There are 8 pages, with 128 bytes in each page. Each byte is a single column “stack” 8 bits high. (See the data sheet.) Here is also a quick and dirty perl program that will read the PGM file and output an array of chars you can paste into your C++ program, it may or may not work:

```perl
#!/usr/bin/perl
$junk = ;
$junk = ;
print $junk;
$junk = ();
print $junk;
chomp $junk;
($cols, $rows, $junk) = split(/\s+/, $junk);
$nbytes = $rows * $cols / 8;
for ($r = 0; $r < $rows; $r++) {
for ($c = 0; $c < $cols; $c++) {
$data[$r][$c] = ;
chomp($data[$r][$c]);
if ($data[$r][$c] > 128) { $data[$r][$c] = 1 }
}
}

/* PGM: 255 is white, 0 is black */
print “// $nbytes bytes in $r rows $c cols\n”;

print “static unsigned char bitmap[] PROGMEM = {\n”;

/* Read 8 pages of columns of 8 bits. Each page is 128 bytes.
LSB of each byte is the “top” of the 8 bits of the column */
for ($page = 0; $page < 8; $page++) {
for ($c = 0; $c < $cols; $c++) {
$byte[$page][$c] = $data[$page8 + 7][$c] * 128 +
$data[$page8 + 6][$c] * 64 +
$data[$page8 + 5][$c] * 32 +
$data[$page8 + 4][$c] * 16 +
$data[$page8 + 3][$c] * 8 +
$data[$page8 + 2][$c] * 4 +
$data[$page8 + 1][$c] * 2 +
$data[$page8 + 0][$c] ;
print "$byte[$page][$c], "
}
print “\n”;
}
print "\n};\n ";
```

