#include "SPIFFS.h"
#include "mjsStuff.h"
#include "EEPROMWrapper.h"
#include "TFTStuff.h"
#include "BleKeyboardStuff.h"

struct AppData {
  TFTCalibrationData tftCalibrationData;
};

EEPROMWrapper<AppData> appData;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.println("Booting");

  if (!SPIFFS.begin()) {
    Serial.println("Formatting file system");
    SPIFFS.format();
    SPIFFS.begin();
  }

  Serial.println("Loading EEPROM");
  appData.begin();
  bool appDataValid = appData.validateCRC();
  if(appDataValid) {
    Serial.println("EEPROM data valid");
  } else {
    Serial.println("EEPROM data invalid");
  }

  TFTStuff_setup(appData.payload.tftCalibrationData, appDataValid);
  BleKeyboardStuff_setup();
  mjsStuff_setup();

  if(!appData.validateCRC()) {
    Serial.println("Updating EEPROM");
    appData.commit();
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  TFTStuff_loop();
  BleKeyboardStuff_loop();
}
