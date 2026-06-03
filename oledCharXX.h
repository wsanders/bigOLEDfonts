// Draw the chars one at a time with these functions. You could make
// it a class, exercise is left to the reader.
// y is going to be an integer between 0 and 7 that is actually y/8
// I don't remember why

void oledChar32(unsigned char thechar, char y, char x) {
  thechar = thechar - 48;
  for (unsigned char page = 0; page < 4; page++) {
    SeeedOled.setXY(y + page, x);
    for (int j = 0; j < 20; j++) {
      SeeedOled.sendData(pgm_read_byte(&font32[thechar][page][j]));
      //SeeedOled.drawBitmap(&fontchar[thechar][page][j],1);
    }
  }
}
void oledChar16(unsigned char thechar, char y, char x) {
  thechar = thechar - 48;
  for (unsigned char page = 0; page < 2; page++) {
    SeeedOled.setXY(y + page, x);
    for (int j = 0; j < 10; j++) {
      SeeedOled.sendData(pgm_read_byte(&font16[thechar][page][j]));
      //SeeedOled.drawBitmap(&fontchar[thechar][page][j],1);
    }
  }
}

void oledChar24(unsigned char thechar, char y, char x) {
  const int charwidth = 14;
  const int charheight = 3; // in pages-1
  thechar = thechar - 48;
  for (unsigned char page = 0; page < charheight; page++) {
    SeeedOled.setXY(y + page, x);
    for (int j = 0; j < charwidth; j++) {
      SeeedOled.sendData(pgm_read_byte(&font24[thechar][page][j]));
    }
  }
}
