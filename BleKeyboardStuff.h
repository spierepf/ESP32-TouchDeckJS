#include <BleKeyboard.h>

#define STATUS_LED LED_BUILTIN

class LocalBleKeyboard : public BleKeyboard {
public:
  size_t write(uint8_t c)
  {
    if(isConnected()) {
      uint8_t p = press(c);
      delay(5);
      release(c);
      delay(20);
      return p;
    }
    return 0;
  }  
};

LocalBleKeyboard bleKeyboard;

void openCommandPrompt() {
  bleKeyboard.press(KEY_LEFT_ALT);
  bleKeyboard.press(KEY_F2);
  delay(100);
  bleKeyboard.releaseAll();
  delay(200);
}

void typeString(char *x) {
  bleKeyboard.print(x);
  delay(100);
  bleKeyboard.releaseAll();
  delay(500);
}

void BleKeyboardStuff_setup() {
  bleKeyboard.begin();
  pinMode(STATUS_LED, OUTPUT);
}

void BleKeyboardStuff_loop() {
  digitalWrite(STATUS_LED, bleKeyboard.isConnected());
}
