#include "EEPROMWrapper.h"
#include "TFTStuff.h"

struct AppData {
  TFTCalibrationData tftCalibrationData;
};

EEPROMWrapper<AppData> appData;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.println("Booting");

  Serial.println("Loading EEPROM");
  appData.begin();
  bool appDataValid = appData.validateCRC();
  if(appDataValid) {
    Serial.println("EEPROM data valid");
  } else {
    Serial.println("EEPROM data invalid");
  }

  TFTStuff_setup(appData.payload.tftCalibrationData, appDataValid);

  if(!appData.validateCRC()) {
    Serial.println("Updating EEPROM");
    appData.commit();
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  TFTStuff_loop();
}