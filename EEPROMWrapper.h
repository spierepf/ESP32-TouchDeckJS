#include <EEPROM.h>
#include <rom/crc.h>

template <class X>
class EEPROMWrapper {
public:
  X payload;

private:
  uint32_t crc;

public:
  void updateCRC() {
    crc = crc32_le(0, (const uint8_t*)&payload, sizeof(payload));
  }

  bool validateCRC() {
    return crc == crc32_le(0, (const uint8_t*)&payload, sizeof(payload));
  }

  void begin() {
    EEPROM.begin(sizeof(payload) + sizeof(crc));
    EEPROM.readBytes(0, &payload, sizeof(payload));
    EEPROM.readBytes(sizeof(payload), &crc, sizeof(crc));
  }

  void commit() {
    updateCRC();
    EEPROM.writeBytes(0, &payload, sizeof(payload));
    EEPROM.writeBytes(sizeof(payload), &crc, sizeof(crc));
    EEPROM.commit();
  }
};
