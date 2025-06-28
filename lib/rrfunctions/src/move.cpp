#include <move.hpp>

using namespace rrobot;


float rrmove::move_d_t(rrstate& s, RrSensors& b) {
    if (!rrfunctions::sen_acc_s(s, b)) {
        return false;
    }
    float x, y, z, a;
    s.get_sens(r_imu_sens::_ACC, a, x, y, z);

    // Example: Using X-axis, and assuming device is flat and gravity is removed
    a = x * GV_M2;  // Convert g to m/s^2
    unsigned long currentTime = millis();
    float dt = (currentTime - s.get_last_time()) / SEC;  // seconds
    s.set_last_time(currentTime);
    s.set_velocity(s.get_velocity() + a * dt); // Integrate acceleration to get velocity
    return s.get_velocity() * dt;  // Integrate velocity to get distance
}

 void rrmove::move_t(rrstate& s, RrSensors& b) {
 }