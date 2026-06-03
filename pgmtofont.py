#!/usr/local/bin/python
import sys
import os
import pprint
debug = 1

def chomp(string):
    return string[:-1]



if len(sys.argv) < 2:
    sys.stderr.write("Usage: sys.argv[0] <PGM ASCII file to read>\n")
    sys.exit(1)
pgmfile = open(sys.argv[1], "r")
junk =  pgmfile.readline()
junk =  pgmfile.readline()
junk =  chomp(pgmfile.readline())
(cols, rows) = junk.split(' ')
rows = int(rows)
cols = int(cols)
print "//", rows, "rows, ", cols, " cols"
# nbytes =  rows * cols / 8;
# PGM bitmap: 255 is white, 0 is black, reverse colors to match OLED

data = []
for r in xrange(rows):
    data.append([])
    for c in xrange(cols):
        pix = (int(chomp(pgmfile.readline())) + 1 ) % 256
        data[r].append(pix)
#pprint.pprint(data)

# Generate a new char every 20 cols
nchars = cols / 20
print "prog_uchar font32[][4][20] PROGMEM = {"
for char in xrange(0, nchars):
    # read groups of 8 rows from col char to char+19
    print "{",
    for page in xrange(4):
        print "{"
        for c in xrange(char*20,char*20 + 20):
            byte = data[page*8 + 7][c] * 128 + \
            data[page*8 + 6][c] *  64 + \
            data[page*8 + 5][c] *  32 + \
            data[page*8 + 4][c] *  16 + \
            data[page*8 + 3][c] *   8 + \
            data[page*8 + 2][c] *   4 + \
            data[page*8 + 1][c] *   2 + \
            data[page*8 + 0][c] 
            print '%ld,' % byte,
        print "},"
    print "},"
print "}"
