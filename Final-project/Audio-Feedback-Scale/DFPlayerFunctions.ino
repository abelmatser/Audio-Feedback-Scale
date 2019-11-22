void DFplayerSetup()
{
  mySoftwareSerial.begin(9600);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card or USB drive!"));
    while (true) {
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);  //Play the first mp3
}

void DFplayerTest()
{
  static unsigned long timer = millis();

  if (millis() - timer > 3000) {
    timer = millis();

    myDFPlayer.next();  //Play next mp3 every 3 second.

    int value;
    //    value = myDFPlayer.readState(); //read mp3 state
    //    value = myDFPlayer.readVolume(); //read current volume
    //    value = myDFPlayer.readEQ(); //read EQ setting
    //    value = myDFPlayer.readFileCounts(); //read all file counts in SD card
    //    value = myDFPlayer.readCurrentFileNumber(); //read current play file number
    //    value = myDFPlayer.readFileCountsInFolder(3); //read file counts in folder SD:/03

    if (value == -1) {  //Error while Reading.
      printDetail(myDFPlayer.readType(), myDFPlayer.read());
    }
    else { //Successfully get the result.
      //      Serial.println(value);
    }
  }


  if (myDFPlayer.available()) {
    printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
  }
}

void playEmotions() {
  if (sensorFSR.outputMass == -1) {
    myDFPlayer.pause();
  }
  else if (sensorFSR.outputMass == 100) {
    myDFPlayer.play(1);
  }
  else if (sensorFSR.outputMass == 200) {
    myDFPlayer.play(2);
  }
  else if (sensorFSR.outputMass == 300) {
    myDFPlayer.play(3);
  }
  else if (sensorFSR.outputMass == 400) {
    myDFPlayer.play(4);
  }
  else if (sensorFSR.outputMass == 500) {
    myDFPlayer.play(5);
  }
  else if (sensorFSR.outputMass == 600) {
    myDFPlayer.play(6);
  }
  else if (sensorFSR.outputMass >  600) {
    myDFPlayer.play(7);
  }
  else {
    Serial.println("No sensorFSR.outputMass known.");
  }
  
  if (sensorFSR.outputMass != -1) {
    songDelay();
  }
}

void songDelay()
{
  Serial.println("Delaying to start song");
  //  Serial.println(myDFPlayer.readState()); //read mp3 state
  delay(3000);
}

void printDetail(uint8_t type, int value) {
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerUSBInserted:
      Serial.println("USB Inserted!");
      break;
    case DFPlayerUSBRemoved:
      Serial.println("USB Removed!");
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }

}
