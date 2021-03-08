#include "mjs.h"

#define BOOT_FILE "/boot.js"

struct mjs *mjs;

void configureButton(const int b, const char* text, const char* command);

void *my_dlsym(void *handle, const char *name) {
  if (strcmp(name, "configureButton") == 0) return (void*)configureButton;
  Serial.print("Unknown function: ");
  Serial.println(name);
  return NULL;
}

void mjs_execute(String& command) {
  mjs_exec(mjs, command.c_str(), NULL);
}

void mjsStuff_setup() {
  mjs = mjs_create();
  mjs_set_ffi_resolver(mjs, my_dlsym);
  mjs_exec(mjs, "let configure_button = ffi('void configureButton(int, char*, char*)');", NULL);

  if (SPIFFS.exists(BOOT_FILE)) {
    File f = SPIFFS.open(BOOT_FILE, "r");
    if (f) {
      size_t len = f.size();
      char buf[len+1];
      if (f.readBytes((char *)buf, len) == len) {
        buf[len]='\0';
        mjs_exec(mjs, buf, NULL);
      }
      f.close();
    }
  }
}
