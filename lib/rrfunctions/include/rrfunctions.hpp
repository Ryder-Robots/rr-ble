#ifndef RRFUNCTIONS_HPP
#define RRFUNCTIONS_HPP

#include <functional>
#include <rrevent.hpp>
#include <rrutil.hpp>

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

// registered functions that will be executed in main loop.
const execfunction _functions[] = {
    none_r,
    sonar_r,
    sen_acc_r,
    sen_gyro_r,
    sen_mag_r,
    stop_r,
    move_r,
    rotate_r,
};
}  // namespace rrfunctions

}  // namespace rrobot
#endif