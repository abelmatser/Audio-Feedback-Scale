#include <Wire.h>
#include <SPI.h>
#include "SH1106.h"
#include "SH1106Ui.h"
#include "emojis.h"

#define OLED_RESET  D1   // RESET
#define OLED_DC     D2   // Data/Command
#define OLED_CS     D8   // Chip select

SH1106 display(true, OLED_RESET, OLED_DC, OLED_CS); // FOR SPI
SH1106Ui ui     ( &display );

bool msOverlay1(SH1106 *display, SH1106UiState* state) {
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(128, 0, String(millis()));
  return true;
}

bool msOverlay2(SH1106 *display, SH1106UiState* state) {
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->setFont(ArialMT_Plain_10);
  display->drawStringMaxWidth(0, 10, 120 , getMood());
  return true;
}

String getMood(){
  if (millis() < 10000) {
    return "Nothing I can't manage!";
  }
  else if (millis() < 20000) {
    return "I can do this";
  }
  else if (millis() < 30000) {
    return "It's getting harder!";
  }
  else if (millis() < 40000) {
    return "Get it off me you bastard!";
  }
  else {
    return "AAAAAAAAAAAAAAAH!";
  }
}

bool msOverlay3(SH1106 *display, SH1106UiState* state) {
  if (millis() < 3000) {
    display->drawXbm(50, 30, Emoji1_width, Emoji1_height, Emoji1_bits);
  }
  else if (millis() < 6000) {
    display->drawXbm(50, 30, Emoji2_width, Emoji2_height, Emoji2_bits);
  }
  else if (millis() < 9000) {
    display->drawXbm(50, 30, Emoji3_width, Emoji3_height, Emoji3_bits);
  }
  else if (millis() < 12000) {
    display->drawXbm(50, 30, Emoji4_width, Emoji4_height, Emoji4_bits);
  }
  else if (millis() < 15000) {
    display->drawXbm(50, 30, Emoji5_width, Emoji5_height, Emoji5_bits);
  }
  else if (millis() < 17000) {
    display->drawXbm(50, 30, Emoji6_width, Emoji6_height, Emoji6_bits);
  }
  else{
    display->drawXbm(50, 30, Emoji7_width, Emoji7_height, Emoji7_bits);
  }
  return true;
}

bool drawFrame(SH1106 *display, SH1106UiState* state, int x, int y) {
  return false;
}
int frameCount = 0;
bool (*frames[])(SH1106 *display, SH1106UiState* state, int x, int y) = {drawFrame};
bool (*overlays[])(SH1106 *display, SH1106UiState* state)             = { msOverlay1, msOverlay2, msOverlay3 };
int overlaysCount = 3;

void setupUI() {
  ui.setTargetFPS(60);
  ui.setActiveSymbole(activeSymbole);
  ui.setInactiveSymbole(inactiveSymbole);
  ui.disableAutoTransition();
  ui.setFrames(frames, frameCount);
  ui.setOverlays(overlays, overlaysCount);
  ui.init();
}

void timeBudget() {
  int remainingTimeBudget = ui.update();
  if (remainingTimeBudget > 0) {
    delay(remainingTimeBudget);
  }
}

void setup() {
  setupUI();
}

void loop() {
  timeBudget();
}
