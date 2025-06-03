#ifndef RRFUNCTIONS_HPP
#define RRFUNCTIONS_HPP

#include <functional>
#include <rrevent.hpp>
#include <rrutil.hpp>

using namespace rrobot;
using execfunction = std::function<rrevent(rrevent, int&)>;

#define RR_MV_ 1
#define RR_ST_ 2
#define RR_RT_ 3

namespace rrobot {
namespace rrfunctions {
const execfunction _functions[] = {};

}  // namespace rrfunctions

}  // namespace rrobot
#endif