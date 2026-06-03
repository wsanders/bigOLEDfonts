Going down memory lane - For my own reference and the general public, recreating the prodecure I deviced in *2013* to generate and use 16, 24, and 32 bit high fonts for the Seeed SSD1308 based OLED display. 
Filling in the repo as a dig up how I did it.

Steps (incomplete):

1) Draw or import a monochrome image of your font into Gimp. ~~Set the canvas size to 128 cols by 64 rows~~ ??.

2) Export the image as a PGM (my copy of Gimp doesn’t seem to be capable of PBM.) PGM has the following format: Two lines of metadata, a third line with the number of cols and number of rows (“128 64”) and successive lines that are rowwise byte by byte pixels in the image. The lines will be either 255 (white) or 0 (black).

3) We have to read the rowwise data and convert it into the “pages” the OLED controller wants. There are 8 pages, with 128 bytes in each page. Each byte is a single column “stack” 8 bits high. (See the data sheet.) Here is quick and dirty perl program that will read the PGM file and output an array of chars you can paste into your C++ program. There also a python utility here in the repo, pgmtofont.py:

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

