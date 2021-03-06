#include "mjs.h"

#define BOOT_FILE "/boot.js"

struct mjs *mjs;

void configureButton(const int b, const char* text, const char* command);
void openCommandPrompt();
void typeString(char *x);

void _delay(int ms) {
  delay(ms);
}

void *my_dlsym(void *handle, const char *name) {
  if (strcmp(name, "_delay") == 0) return (void*)_delay;
  if (strcmp(name, "configureButton") == 0) return (void*)configureButton;
  if (strcmp(name, "openCommandPrompt") == 0) return (void*)openCommandPrompt;
  if (strcmp(name, "typeString") == 0) return (void*)typeString;

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
  mjs_exec(mjs, "let delay = ffi('void _delay(int)');", NULL);
  mjs_exec(mjs, "let configure_button = ffi('void configureButton(int, char*, char*)');", NULL);
  mjs_exec(mjs, "let open_command_prompt = ffi('void openCommandPrompt(void)');", NULL);
  mjs_exec(mjs, "let type_string = ffi('void typeString(char*)');", NULL);

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
