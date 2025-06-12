#ifndef RRSTATE_HPP
#define RRSTATE_HPP

#include <rrblemappings.hpp>

namespace rrobot {
class rrstate {
   public:
    rrstate() = default;
    ~rrstate() = default;

    void set_cstate(int cstate) { _cstate = cstate; }

    int get_cstate() { return _cstate; }

    void set_ena(int ena) { _ena = ena; }

    int get_ena() { return _ena; }

    void set_enb(int enb) { _enb = enb; }

    int get_enb() { return _enb; }

    void set_in1(int in1) { _in1 = in1; }

    int get_in1() { return _in1; }

    void set_in2(int in2) { _in2 = in2; }

    int get_in2() { return _in2; }

    void set_in3(int in3) { _in3 = in3; }

    int get_in3() { return _in3; }

    void set_in4(int in4) { _in4 = in4; }

    int get_in4() { return _in4; }

   private:
    int _cstate = RR_ST_;
    int _ena = 0;
    int _enb = 0;
    int _in1 = 0;
    int _in2 = 0;
    int _in3 = 0;
    int _in4 = 0;
};
}  // namespace rrobot

#endif