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