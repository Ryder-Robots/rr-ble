#ifndef MOVE_HPP
#define MOVE_HPP

#include <rrfunctions.hpp>

namespace rrobot {

namespace rrmove {
/**
 * @brief Calculates the distance moved over time.
 *
 * This function computes the distance traveled based on the current robot state and sensor readings.
 *
 * @param s Reference to the current robot state.
 * @param b Reference to the sensor readings.
 * @return The distance moved as a float.
 */
float move_d_t(rrstate& s, RrSensors& b);

void move_t(rrstate& s, RrSensors& b, double& input, double& output);
}  // namespace rrmove
}  // namespace rrobot

#endif