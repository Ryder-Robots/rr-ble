#include <rrobot.hpp>

using namespace rrobot;

// PID variables
double setpoint = 0;
double input = 0;
double output = 0;  // Desired heading (forward)
// Current heading (from gyro)
// PID correction
// PID tuning parameters
PID _pid(&input, &output, &setpoint, r_pid::_KP, r_pid::_KI, r_pid::_KD, DIRECT);

// contains current state of robot during movements
rrstate cstate_(_pid);
RRBle ble_;

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
    if (!ble_.begin()) {
        rrevent e = rrevent(MSP_NONE);
        Serial.print(serde::serialize(rrfunctions::_functions[POS(e.get_cmd())](e, cstate_, ble_)));

        // hard block here.
        while (1) {
        }
    }

    // TODO need to initilize sonar here

    // initlize PID algorithm
    _pid.SetMode(AUTOMATIC);
    // Correction range, this can be added to mappings as a constant.
    _pid.SetOutputLimits(r_pid::_OUT_LIMIT_LOW, r_pid::_OUT_LIMIT_HIGH);
}

void executeCommand() {
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
    sz = Serial.print(serde::serialize(rrfunctions::_functions[POS(e.get_cmd())](e, cstate_, ble_)));
}

void loop() {
    if (Serial.available()) {
        executeCommand();
    }
    if (cstate_.get_cstate() == RR_MV_) {
        rrmove::move_t(cstate_, ble_, input, output);
    } else {
        delay(rrhbridge_map::_SAMPLE_TIME);
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
