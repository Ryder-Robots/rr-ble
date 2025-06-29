#include <move.hpp>

using namespace rrobot;

float rrmove::move_d_t(rrstate& s, RrSensors& b) {
    if (!rrfunctions::sen_acc_s(s, b)) {
        return false;
    }
    float x, y, z, a;
    s.get_sens(r_imu_sens::_ACC, a, x, y, z);

    // Example: Using X-axis, and assuming device is flat and gravity is removed
    a = z * GV_M2;  // Convert g to m/s^2
    unsigned long currentTime = millis();
    float dt = (currentTime - s.get_last_time()) / SEC;  // seconds
    s.set_last_time(currentTime);
    s.set_velocity(s.get_velocity() + a * dt);  // Integrate acceleration to get velocity
    return s.get_velocity() * dt;               // Integrate velocity to get distance
}


void rrmove::move_t(rrstate& s, RrSensors& b, double& input, double& output) {
    float x, y, z, a;
    int d = s.get_distance_delta();
    if (d <= 0) {
        s.set_cstate(RR_SS_);
    }

    s.get_sens(r_imu_sens::_GYRO, a, x, y, z);
    input += z * rrhbridge_map::_SAMPLE_TIME / 100;
    s.get_pid().Compute();
    s.set_ena(constrain(rrhbridge_map::_PWM_VALUE - output, 0, 255));
    s.set_enb(constrain(rrhbridge_map::_PWM_VALUE + output, 0, 255));

    rrfunctions::move_s(s, b);
    delay(rrhbridge_map::_SAMPLE_TIME);
    s.set_distance_delta(d -= move_d_t(s, b));
    s.set_distance_total(d);
}