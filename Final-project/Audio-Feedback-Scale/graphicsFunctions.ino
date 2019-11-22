bool msOverlay1(SH1106 *display, SH1106UiState* state) {
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(128, 0, String(millis()));
  return true;
}

String printText(String text){
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->setFont(ArialMT_Plain_10);
  display->drawStringMaxWidth(0, 15, 120 , text);
}

bool msOverlay2(SH1106 *display, SH1106UiState* state) {
  if (sensorFSR.outputMass == 100) {
    printText("This is too easy for me");
    display->drawXbm(50, 30, Emoji1_width, Emoji1_height, Emoji1_bits);
  }
  else if (sensorFSR.outputMass == 200) {
    printText("Nothing I can't manage!");
    display->drawXbm(50, 30, Emoji2_width, Emoji2_height, Emoji2_bits);
  }
  else if (sensorFSR.outputMass == 300) {
    printText("It's getting harder, slow down");
    display->drawXbm(50, 30, Emoji3_width, Emoji3_height, Emoji3_bits);
  }
  else if (sensorFSR.outputMass == 400) {
    printText("This is enough!");
    display->drawXbm(50, 30, Emoji4_width, Emoji4_height, Emoji4_bits);
  }
  else if (sensorFSR.outputMass == 500) {
    printText("Get this off me you bastard!");
    display->drawXbm(50, 30, Emoji5_width, Emoji5_height, Emoji5_bits);
  }
  else if (sensorFSR.outputMass == 600) {
    printText("Fuck off fat fuck!");
    display->drawXbm(50, 30, Emoji6_width, Emoji6_height, Emoji6_bits);
  }
  else if (sensorFSR.outputMass > 600) {
    printText("AAAAAAAAAAAAAAAAAAAAAH");
    display->drawXbm(50, 30, Emoji7_width, Emoji7_height, Emoji7_bits);
  }
  else{
    // Display nothing
  }
  return true;
}

bool drawFrame(SH1106 *display, SH1106UiState* state, int x, int y) {
  return false;
}
int frameCount = 0;
bool (*frames[])(SH1106 *display, SH1106UiState* state, int x, int y) = {drawFrame};
bool (*overlays[])(SH1106 *display, SH1106UiState* state)             = { msOverlay1, msOverlay2};
int overlaysCount = 2;

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
