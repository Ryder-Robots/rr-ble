#ifndef RRFUNCTIONS_HPP
#define RRFUNCTIONS_HPP

#include <functional>
#include <rrblemappings.hpp>
#include <rrerror.hpp>
#include <rrevent.hpp>
#include <rrstate.hpp>
#include <rrutil.hpp>
#include <rrble.hpp>

using namespace rrobot;
using execfunction = std::function<rrevent(rrevent&, rrstate&, RrSensors&)>;

// instructs command loop to continue on with last action.
#define RR_NN_ 4

// limit float to two decimal places
#define RR_F_2(X) atof(String(atof(X.c_str()).c_str(), 2))
#define _UT_SCALED(X) X / MAX_UT
#define DG(R) R * (180 / PI)

namespace rrobot {
namespace rrfunctions {

// state only functions for sensors
bool sen_acc_s(rrstate& s, RrSensors& b);
bool sen_gyro_s(rrstate& s, RrSensors& b);
bool sen_mag_s(rrstate& s, RrSensors& b);
bool move_s(rrstate& s, RrSensors& b);
bool stop_s(rrstate& s, RrSensors& b);

// list of events that can be triggered
rrevent none_r(rrevent e, rrstate& s, RrSensors& b);
rrevent sonar_r(rrevent e, rrstate& s, RrSensors& b);
rrevent sen_acc_r(rrevent e, rrstate& s, RrSensors& b);
rrevent sen_gyro_r(rrevent e, rrstate& s, RrSensors& b);
rrevent sen_mag_r(rrevent e, rrstate& s, RrSensors& b);
rrevent stop_r(rrevent e, rrstate& s, RrSensors& b);
rrevent move_r(rrevent e, rrstate& s, RrSensors& b);
rrevent rotate_r(rrevent e, rrstate& s, RrSensors& b);
rrevent status_r(rrevent e, rrstate& s, RrSensors& b);

/**
 * @brief get heading in degrees. Headings are mapped according to uTs, where magnometer will return the gravitation
 * force (approximately 50uT at sea level). The formula will convert x, y vector to degrees,  which can be approximated
 * as:
 *
 *  || Vector    || Othagonal  || Degrees   || Radians
 *  +------------+-------------+------------+--------------
 *  | <0,1>      | east        | 90         | 1.5708
 *  | <0,-1>     | west        | -90        | 4.7124
 *  | <1,0>      | north       | 0          | 0.0
 *  | <-1,0>     | move south. | 180        | 3.1416
 *  | <1,1>      | north east  | 45         | 0.7071
 *  | <1,-1>     | north west. | -45        | 0
 *  | <-1,1>     | south east. | 135        |
 *  | <-1,-1>    | south west  | -135       |
 */
int heading_d(float x, float y, float z);

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
 *   - 224:  MSP_STATUS
 */
// registered functions that will be executed in main loop.
const execfunction _functions[] = {
    none_r,      // 0
    sonar_r,     // 1
    sen_acc_r,   // 2
    sen_gyro_r,  // 3
    sen_mag_r,   // 4
    stop_r,      // 5
    move_r,      // 6
    rotate_r,    // 7
    status_r,    // 8
};
}  // namespace rrfunctions

}  // namespace rrobot
#endif