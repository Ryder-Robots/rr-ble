#ifndef RUTIL_HPP
#define RUTIL_HPP

#include <Arduino.h>

/**
 * @file rrutil.hpp
 * @brief Utility functions for the rrobot project.
 *
 * This header provides utility functions for string manipulation and searching arrays,
 * designed for use with Arduino-based projects.
 */

namespace rrobot {

#define RLEN(X) (sizeof(X) / sizeof(X[0]))
#define POS(X) binary_search(RR_COMMANDS, RR_CMDSZ, X)

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
 *   - 221:  MSP_MOVE
 *   - 223:  MSP_ROTATE
 *   - 220:  MSP_STOP

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

const int RR_CMDSZ = 7;
const size_t RR_MX_E_SZ = 100;
const char _TERM_CHAR = 0x1E;
const char _DELIMETER = 0x3B;

/**
 * @brief Splits a string into parts based on a delimiter.
 *
 * @param input The input string to split.
 * @param delimiter The character used to split the string.
 * @param results An array of String objects to store the split parts.
 * @param maxParts The maximum number of parts to split into.
 * @return The number of parts the string was split into.
 */
int split_string(const String &input, char delimiter, String results[], int maxParts);

/**
 * @brief Performs a binary search on a sorted array of integers.
 *
 * @param arr The sorted array to search.
 * @param size The number of elements in the array.
 * @param target The value to search for.
 * @return The index of the target if found, otherwise -1.
 */
int binary_search(const int arr[], int size, int target);

}  // namespace rrobot

#endif