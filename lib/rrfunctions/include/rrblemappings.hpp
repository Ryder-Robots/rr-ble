
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


namespace rrobot {
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
    const int _IN1 = 5;
    const int _IN2 = 6;
    const int _IN3 = 2;
    const int _IN4 = 3;
    const int _ENA = 7;
    const int _ENB = 4;

    const int _PWM_VALUE = 255/2;
}

namespace rserial {
    const int _BOARDRATE = 9600;
}

namespace r_imu_po {
    const int _AVAIL_P = 0;
    const int _X_P = 1;
    const int _Y_P = 2;
    const int _Z_P = 3;
}
}  // namespace rrobot

#endif