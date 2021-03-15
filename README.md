# ESP32-TouchDeckJS

This project was inspired by https://github.com/DustinWatts/FreeTouchDeck

This touch deck project is configured using a subset of JavaScript called [mjs](https://github.com/cesanta/mjs). Besides the JS functions implemented by mjs, this project adds the following four functions:

- `delay(ms)` which causes a delay of an integer number of milliseconds.
- `configure_button(pos, label, code)` which configures the button in position `pos` to display the label `label` and execute the js code `code` when pressed.
- `open_command_prompt()` which uses the bluetooth keyboard emulation to signal Alt-F2 which opens the command prompt on my box. (You can modify `openCommandPrompt` in `BleKeyboardStuff.h` to reimplement for your setup).
- `type_string(text)` which types the given string using bluetooth keyboard emulation.

When this sketch starts, it searches the ESP32 SPIFFS for a `boot.js` file, which it loads and executes. The default one in `data/boot.js` simply configures each button to send its position over the serial port whenever it is triggered.

You can upload `data/boot.js` using the [filesystem uploader tool](https://randomnerdtutorials.com/install-esp32-filesystem-uploader-arduino-ide/)

You will need to have the [BleKeyboard](https://github.com/T-vK/ESP32-BLE-Keyboard) and [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI) both of which are available in the the Arduino Library Manager. You will have to configure the TFT_eSPI library's [`User_Setup.h`](https://github.com/Bodmer/TFT_eSPI/blob/master/User_Setup.h) file for your touch screen display.

Also, this sketch uses the onboard LED (see [`BleKeyboardStuff.h`](https://github.com/spierepf/ESP32-TouchDeckJS/blob/develop/BleKeyboardStuff.h)) to show when the device has bluetooth connectivity. The LED is lit when the board is disconnected.

## References
https://github.com/cesanta/mjs
