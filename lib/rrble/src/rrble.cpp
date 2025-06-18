#include <rrble.hpp>

using namespace rrobot;

int RRBle::begin() {
   return IMU.begin();
}

void RRBle::end() {}

int RRBle::readAcceleration(float& x, float& y, float& z) {
    return IMU.readAcceleration(x, y, z);
}

int RRBle::accelerationAvailable() {
    return IMU.accelerationAvailable();
}

int RRBle::readGyroscope(float& x, float& y, float& z) {
    return IMU.readGyroscope(x, y, z);
}

int RRBle::gyroscopeAvailable() {
    return IMU.gyroscopeAvailable();
}

int RRBle::readMagneticField(float& x, float& y, float& z) {
    return IMU.readMagneticField(x, y, z);
}

int RRBle::magneticFieldAvailable() {
    return IMU.magneticFieldAvailable();
}