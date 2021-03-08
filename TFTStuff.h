#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

struct TFTCalibrationData {
  uint16_t data[5];
};

#define REPEAT_CAL false

void touch_calibrate(TFTCalibrationData& calibrationData, bool calibrationDataOK)
{
  if (calibrationDataOK && !REPEAT_CAL) {
    tft.setTouch(calibrationData.data);
  } else {
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(20, 0);
    tft.setTextFont(2);
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.println("Touch corners as indicated");

    tft.setTextFont(1);
    tft.println();

    if (REPEAT_CAL) {
      tft.setTextColor(TFT_RED, TFT_BLACK);
      tft.println("Set REPEAT_CAL to false to stop this running again!");
    }

    tft.calibrateTouch(calibrationData.data, TFT_MAGENTA, TFT_BLACK, 15);

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.println("Calibration complete!");
  }
}

void TFTStuff_setup(TFTCalibrationData& calibrationData, bool appDataValid) {
  tft.init();
  tft.setRotation(3);
  touch_calibrate(calibrationData, appDataValid);
  tft.fillScreen(TFT_BLACK);
}

void TFTStuff_loop() {
  
}
