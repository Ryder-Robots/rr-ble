#include <rrobot.hpp>

using namespace rrobot;

void setup() {
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
      uint8_t buf[BUFSIZ];
      Serial.readBytesUntil(_TERM_CHAR, buf, BUFSIZ);

      // check last char is _TERM_CHAR

      String s = String(reinterpret_cast<char*>(buf));
      rrevent e = rringress::deserialize(s);
  }
}

#ifdef NATIVE
/**
 * @fn main
 * @brief
 * main method added so that code can be compiled using native environment with library ArduinoFake
 */
int main() {
    setup();
    while (1) {
        loop();
    }
    return 0;
}

#endif
