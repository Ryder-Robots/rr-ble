#ifndef RRERROR_HPP
#define RRERROR_HPP

#include <rrutil.hpp>

namespace rrobot {
namespace rrerror {
const String err_term[] = {"1", "can not deserialize input"};
const String err_noimp[] = {"2", "function has not been implemented"};
const String err_noimu[] = {"3", "IMU data is not available for sensor"};
}  // namespace rrerror
}  // namespace rrobot

#endif