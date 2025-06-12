#include <rrobot.hpp>

using namespace rrobot;

// contains current state of robot during movements
int cstate_ = RR_ST_;

// TODO: add timer to here, that also includes movement commands for callback
void setup() {
    // Initlilize USB first!!!!
    Serial.begin(rserial::_BOARDRATE);

    // configure H bridge
    for (auto i : {rrhbridge_map::_ENA, rrhbridge_map::_ENB, rrhbridge_map::_IN1, rrhbridge_map::_IN2,
                   rrhbridge_map::_IN3, rrhbridge_map::_IN4}) {
        pinMode(i, OUTPUT);
    }

    // Initilize IMU
    if (!IMU.begin()) {
        rrevent e = rrevent(MSP_NONE);
        Serial.print(serde::serialize(rrfunctions::_functions[POS(e.get_cmd())](e, cstate_)));

        // hard block here.
        while (1) {
        }
    }

    //TODO need to initilize sonar here
}

void loop() {
    // put your main code here, to run repeatedly:
    if (!Serial.available()) {
        rrevent e = rrevent(MSP_NONE);
        return;
    }
    char buf[BUFSIZ];
    size_t sz = Serial.readBytesUntil(_TERM_CHAR, buf, BUFSIZ);

    // check last char is _TERM_CHAR
    if (sz == 0) {
        rrevent e = rrevent(MSP_NONE, 2, rrerror::err_term);
        sz = Serial.print(serde::serialize(e));
        return;
    }

    // convert termination character to nullptr
    buf[sz] = '\0';
    String s(buf);
    rrevent e = serde::deserialize(s);
    sz = Serial.print(serde::serialize(rrfunctions::_functions[POS(e.get_cmd())](e, cstate_)));
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
