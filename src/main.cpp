#include <rrobot.hpp>

using namespace rrobot;

// contains current state of robot during movements
int cstate_ = RR_ST_;

// TODO: add timer to here, that also includes movement commands for callback
void setup() {}

void loop() {
    // put your main code here, to run repeatedly:
    if (!Serial.available()) {
        return;
    }
    char buf[BUFSIZ];
    const size_t sz = Serial.readBytesUntil(_TERM_CHAR, buf, BUFSIZ);

    // check last char is _TERM_CHAR
    if (sz > 0 && buf[sz - 1] != _TERM_CHAR) {
        return;
    }

    // convert termination character to nullptr 
    buf[sz - 1] = '\0';
    String s(buf);
    rrevent e = rringress::deserialize(s);
    if (e.get_cmd() == RR_COMMANDS[MSP_NONE]) {
        return;
    }

    // get next action command.  TODO: need to send result back.
    rrfunctions::_functions[e.get_cmd()](e, cstate_);
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
