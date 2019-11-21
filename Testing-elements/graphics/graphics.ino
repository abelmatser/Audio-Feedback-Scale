#include <Wire.h>
#include <SPI.h>
#include "SH1106.h"
#include "SH1106Ui.h"
#include "emojis.h"

//#define OLED_RESET  D1   // RESET
//#define OLED_DC     D2   // Data/Command
//#define OLED_CS     D8   // Chip select

// Pin definitions for I2C
#define OLED_SDA    D2  // pin 14
#define OLED_SDC    D4  // pin 12
#define OLED_ADDR   0x3C

//SH1106 display(true, OLED_RESET, OLED_DC, OLED_CS); // FOR SPI
SH1106   display(OLED_ADDR, OLED_SDA, OLED_SDC);
SH1106Ui ui     ( &display );


void setup() {
  setupUI();
}

void loop() {
  timeBudget();
}
