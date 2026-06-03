// Uses a 32-bit-high font to write to the OLED screen.


#include <Wire.h>
#include <SeeedOLED.h>
#include <font32progmem.h>
#include <avr/pgmspace.h>

// 32bit OLED font

// Font contains only the ASCII chars 0 through capital Z plus space (decimal 48 to 90)
// with the exception that ASCII character 91 is "space".
// Each charcater is 20 pixels wide, 32 pixels high (4 OLED "pages" high)
// See the SSD1308 manual for how each char is written 20 bytes at a time, OLED-page-wise.
// 
// Additional notes on how the array was generated are published separately

int bright=128;

void setup()
{
  Wire.begin();	
  SeeedOled.init(); 
  SeeedOled.clearDisplay(); 
  SeeedOled.setNormalDisplay();  
  SeeedOled.deactivateScroll();
  SeeedOled.setPageMode();
  SeeedOled.setBrightness(bright);
}

void loop() {
    for (int ascii=48; ascii <92; ascii+=6) {
        sendChar32(ascii,2,0);
        sendChar32(ascii+1,2,20);
        sendChar32(ascii+2, 2,40);
        sendChar32(ascii+3, 2,60);
        sendChar32(ascii+4, 2,80);
        sendChar32(ascii+5, 2,100);
        delay(2000);
    }
}

void sendChar32(unsigned char thechar, char y, char x) {
    thechar = thechar - 48;
    for (unsigned char page=0; page < 4; page++) {
        SeeedOled.setXY(y+page,x);
        for (int j=0; j<20; j++) {
            SeeedOled.sendData(pgm_read_byte(&font32[thechar][page][j]));
        }
    }
}
