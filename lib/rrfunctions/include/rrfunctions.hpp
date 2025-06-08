#ifndef RRFUNCTIONS_HPP
#define RRFUNCTIONS_HPP

#include <functional>
#include <rrblemappings.hpp>
#include <rrevent.hpp>
#include <rrutil.hpp>
#include "Arduino_BMI270_BMM150.h"

using namespace rrobot;
using execfunction = std::function<rrevent(rrevent&, int&)>;

#define RR_ST_ 220
#define RR_MV_ 221
#define RR_RT_ 223

// instructs command loop to continue on with last action.
#define RR_NN_ 4

namespace rrobot {

namespace rrfunctions {

// list of events that can be triggered
rrevent none_r(rrevent e, int& s);
rrevent sonar_r(rrevent e, int& s);
rrevent sen_acc_r(rrevent e, int& s);
rrevent sen_gyro_r(rrevent e, int& s);
rrevent sen_mag_r(rrevent e, int& s);
rrevent stop_r(rrevent e, int& s);
rrevent move_r(rrevent e, int& s);
rrevent rotate_r(rrevent e, int& s);

/**
 * @fn move_t
 * @brief Initiates a movement operation by interacting with the H-bridge motor driver.
 *
 * This function is responsible for controlling the H-bridge hardware to drive the motors,
 * enabling movement of the system. It should be called when a movement command is required.
 * The implementation is expected to handle all necessary logic to safely and efficiently
 * operate the H-bridge circuitry.
 */
void move_t(int& s);

// registered functions that will be executed in main loop.
const execfunction _functions[] = {
    none_r, sonar_r, sen_acc_r, sen_gyro_r, sen_mag_r, stop_r, move_r, rotate_r,
};
}  // namespace rrfunctions

}  // namespace rrobot
#endif