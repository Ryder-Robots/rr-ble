#include <rrobot.hpp>

using namespace rrobot;

void setup() {}

void loop() {
    // put your main code here, to run repeatedly:
    if (!Serial.available()) {
        return;
    }
    uint8_t buf[BUFSIZ];
    const size_t sz = Serial.readBytesUntil(_TERM_CHAR, buf, BUFSIZ);

    // check last char is _TERM_CHAR
    if (sz > 0 && buf[sz - 1] != _TERM_CHAR) {
        return;
    }

    String s = String(reinterpret_cast<char*>(buf));
    rrevent e = rringress::deserialize(s);
    if (e.get_cmd() == RR_COMMANDS[MSP_NONE]) {
        return;
    }

    // get next action command.
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
