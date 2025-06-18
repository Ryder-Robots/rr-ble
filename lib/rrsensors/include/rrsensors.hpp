/**
 * @brief Interface for chipset sensor access.
 *
 * This abstract class defines the interface for interacting with various sensors
 * (acceleration, gyroscope, and magnetic field) on a chipset. Implementations of this
 * interface should provide the underlying hardware-specific logic for sensor initialization,
 * data reading, and availability checks.
 *
 * Usage:
 * - Call begin() to initialize the sensor hardware.
 * - Use readAcceleration(), readGyroscope(), and readMagneticField() to obtain sensor data.
 * - Use accelerationAvailable(), gyroscopeAvailable(), and magneticFieldAvailable() to check
 *   if new sensor data is available.
 * - Call end() to deinitialize or power down the sensors.
 */
#ifndef RRSENSORS_HPP
#define RRSENSORS_HPP

namespace rrobot {
class RrSensors {
   public:
    virtual int begin() = 0;
    virtual void end() = 0;

    virtual int readAcceleration(float& x, float& y, float& z) = 0;
    virtual int accelerationAvailable() = 0;

    virtual int readGyroscope(float& x, float& y, float& z) = 0;
    virtual int gyroscopeAvailable() = 0;

    virtual int readMagneticField(float& x, float& y, float& z) = 0;
    virtual int magneticFieldAvailable() = 0;
};
}  // namespace rrobot

#endif