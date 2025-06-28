
/**
 * @file rrblemappings.hpp
 * @brief Pin mapping definitions for interfacing an H-bridge motor driver with Arduino Nano 33 BLE.
 *
 * This header defines constant integer values representing the digital IO pins on the Arduino Nano 33 BLE
 * that are connected to the control and enable lines of an H-bridge motor driver. These mappings abstract
 * the physical wiring between the microcontroller and external sensors, or circuits.
 *
 * @note The pin numbers correspond to the Arduino Nano 33 BLE's digital IO numbering.
 */
#ifndef RRBLEMAPPING_HPP
#define RRBLEMAPPING_HPP

#include <Arduino.h>

#define RLEN(X) (sizeof(X) / sizeof(X[0]))
#define POS(X) binary_search(RR_COMMANDS, RR_CMDSZ, X)
#define MIN_UT -400
#define MAX_UT 400

// gravitation using meters per second.
#define GV_M2 9.80665
#define SEC 10000.00

const int RR_CMDSZ = 8;
const size_t RR_MX_E_SZ = 100;
const char _TERM_CHAR = 0x1E;
const char _DELIMETER = 0x3B;

#define RR_ST_ 220
#define RR_MV_ 221
#define RR_RT_ 223

/*
 * Precompiler helpers for when Digitial variable are not defined.
 */
#ifndef D1
#define D1 1
#endif
#ifndef D2
#define D2 2
#endif
#ifndef D3
#define D3 3
#endif
#ifndef D4
#define D4 4
#endif
#ifndef D5
#define D5 5
#endif
#ifndef D6
#define D6 6
#endif
#ifndef D7
#define D7 7
#endif

namespace rrobot {

/**
 * @brief Array of command identifiers used by the rrobot system.
 *
 * Each element in the array corresponds to a specific command, with the index
 * representing the command's position and the value representing its unique identifier.
 * The commands include:
 *   -  0:   MSP_NONE
 *   - 58:   MSP_SONAR_ALTITUDE
 *   - 216:  MSP_SENSOR_ACC
 *   - 217:  MSP_SENSOR_GYRO
 *   - 218:  MSP_SENSOR_MAG
 *   - 220:  MSP_STOP
 *   - 221:  MSP_MOVE
 *   - 223:  MSP_ROTATE
 *
 * These identifiers are used for communication and control within the rrobot system.
 */
const int RR_COMMANDS[] = {
    0,    // MSP_NONE
    58,   // MSP_SONAR_ALTITUDE
    216,  // MSP_SENSOR_ACC
    217,  // MSP_SENSOR_GYRO
    218,  // MSP_SENSOR_MAG
    220,  // MSP_STOP
    221,  // MSP_MOVE
    223,  // MSP_ROTATE
};

const int MSP_NONE = 0;
const int MSP_SONAR_ALTITUDE_P = 1;
const int MSP_SENSOR_ACC_P = 2;
const int MSP_SENSOR_GYRO_P = 3;
const int MSP_SENSOR_MAG_P = 4;
const int MSP_STOP_P = 5;
const int MSP_MOVE_P = 6;
const int MSP_ROTATE_P = 7;

/**
 * @headerfile rrhbridge_map
 * @brief Defines constant mappings for digital IO ports used to control an H-bridge motor driver.
 *
 * This header provides named constants corresponding to the digital IO pins
 * that interface with an H-bridge. These constants (_IN1, _IN2, _IN3, _IN4, _ENA, _ENB)
 * represent the microcontroller's pin numbers connected to the H-bridge's control and enable lines.
 *
 * - _IN1, _IN2: Control inputs for the first motor channel.
 * - _IN3, _IN4: Control inputs for the second motor channel.
 * - _ENA: Enable pin for the first motor channel.
 * - _ENB: Enable pin for the second motor channel.
 *
 * Use these constants to abstract hardware pin assignments in your code, improving readability
 * and maintainability when interfacing with the H-bridge.
 */
namespace rrhbridge_map {
const int _IN1 = D5;
const int _IN2 = D6;
const int _IN3 = D2;
const int _IN4 = D3;
const int _ENA = D7;
const int _ENB = D4;

const int _PWM_VALUE = 255;
const int _SAMPLE_TIME = 50;
}  // namespace rrhbridge_map

namespace rserial {
const int _BOARDRATE = 9600;
}

namespace r_imu_po {
const int _AVAIL_P = 0;
const int _X_P = 1;
const int _Y_P = 2;
const int _Z_P = 3;

const int _SENS_SZ = 4;
}  // namespace r_imu_po

namespace r_imu_sens {
const int _GYRO = 0;
const int _MAG = 1;
const int _ACC = 2;
const int _SENS_SZ = 3;
}  // namespace r_imu_sens
}  // namespace rrobot

#endif