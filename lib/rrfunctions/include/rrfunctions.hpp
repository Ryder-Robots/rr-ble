#ifndef RRFUNCTIONS_HPP
#define RRFUNCTIONS_HPP

#include <functional>
#include <rrstate.hpp>
#include <rrblemappings.hpp>
#include <rrevent.hpp>
#include <rrutil.hpp>
#include <rrerror.hpp>
#include "Arduino_BMI270_BMM150.h"

using namespace rrobot;
using execfunction = std::function<rrevent(rrevent&, rrstate&)>;

// instructs command loop to continue on with last action.
#define RR_NN_ 4

// limit float to two decimal places
#define RR_F_2(X)  atof(String(atof(X.c_str()).c_str(),2))

#define MIN_UT -400
#define MAX_UT 400
#define _UT_SCALED(X) X / MAX_UT
#define DG(R) R * (180/PI) 

namespace rrobot {

namespace rrfunctions { 

// list of events that can be triggered
rrevent none_r(rrevent e, rrstate& s);
rrevent sonar_r(rrevent e, rrstate& s);
rrevent sen_acc_r(rrevent e, rrstate& s);
rrevent sen_gyro_r(rrevent e, rrstate& s);
rrevent sen_mag_r(rrevent e, rrstate& s);
rrevent stop_r(rrevent e, rrstate& s);
rrevent move_r(rrevent e, rrstate& s);
rrevent rotate_r(rrevent e, rrstate& s);

void move_t(rrstate& s);

/**
 * @brief get heading in degrees
 */
float heading_d(float x, float y, float z);

/**
 * @brief get heading in degrees from gyro scope.
 */
float heading_d_gyro(rrstate& s);

/*
 *   - 58:   MSP_SONAR_ALTITUDE
 *   - 216:  MSP_SENSOR_ACC
 *   - 217:  MSP_SENSOR_GYRO
 *   - 218:  MSP_SENSOR_MAG
 *   - 220:  MSP_STOP
 *   - 221:  MSP_MOVE
 *   - 223:  MSP_ROTATE
 */
// registered functions that will be executed in main loop.
const execfunction _functions[] = {
    none_r,     // 0
    sonar_r,    // 1 
    sen_acc_r,  // 2 
    sen_gyro_r, // 3 
    sen_mag_r,  // 4
    stop_r,     // 5 
    move_r,     // 6
    rotate_r,   // 7
};
}  // namespace rrfunctions

}  // namespace rrobot
#endif