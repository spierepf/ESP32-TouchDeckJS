#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

struct TFTCalibrationData {
  uint16_t data[5];
};

#define REPEAT_CAL false

#define NUM_ROWS 2
#define NUM_COLS 3
#define NUM_BUTTONS NUM_ROWS * NUM_COLS

#define SCREEN_W 480
#define SCREEN_H 320

#define BUTTON_SPACING_X 10
#define BUTTON_SPACING_Y 10
#define BUTTON_W ((SCREEN_W / NUM_COLS) - BUTTON_SPACING_X)
#define BUTTON_H ((SCREEN_H / NUM_ROWS) - BUTTON_SPACING_Y)
#define BUTTON_X ((SCREEN_W / NUM_COLS / 2))
#define BUTTON_Y ((SCREEN_H / NUM_ROWS / 2))
#define BUTTON_TEXTSIZE 1

TFT_eSPI_Button button[NUM_BUTTONS];

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

void drawButton(uint8_t b) {
  tft.setFreeFont(&FreeSansBold18pt7b);
  button[b].drawButton(button[b].isPressed());
}

void TFTStuff_setup(TFTCalibrationData& calibrationData, bool appDataValid) {
  tft.init();
  tft.setRotation(3);
  touch_calibrate(calibrationData, appDataValid);
  tft.fillScreen(TFT_BLACK);

  for (uint8_t b = 0; b < NUM_BUTTONS; b++) {
    uint8_t col = b % NUM_COLS;
    uint8_t row = b / NUM_COLS;
    button[b].initButton(&tft, BUTTON_X + col * (BUTTON_W + BUTTON_SPACING_X), BUTTON_Y + row * (BUTTON_H + BUTTON_SPACING_Y), BUTTON_W, BUTTON_H, TFT_WHITE, TFT_BLUE, TFT_WHITE, "", BUTTON_TEXTSIZE);

    drawButton(b);
  }
}

void TFTStuff_loop() {
  uint16_t t_x = 0, t_y = 0; // To store the touch coordinates

  boolean pressed = tft.getTouch(&t_x, &t_y);

  for (uint8_t b = 0; b < NUM_BUTTONS; b++) {
    if (pressed && button[b].contains(t_x, t_y)) {
      button[b].press(true);
    } else {
      button[b].press(false);
    }
  }

  for (uint8_t b = 0; b < NUM_BUTTONS; b++) {
    if (button[b].justPressed() || button[b].justReleased()) {
      drawButton(b);
    }
  }
}
