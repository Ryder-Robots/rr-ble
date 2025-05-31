#ifndef RUTIL_HPP
#define RUTIL_HPP

#include <Arduino.h>

namespace rrobot {
    int split_string(const String& input, char delimiter, String results[], int maxParts);
}

#endif