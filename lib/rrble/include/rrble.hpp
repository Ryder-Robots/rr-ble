#ifndef RRBLE_HPP
#define RRBLE_HPP

#include <rrsensors.hpp>

#include "Arduino_BMI270_BMM150.h"

namespace rrobot {
/**
 * @class RrBle
 * @brief BLE-enabled sensor interface extending RrSensors.
 */
class RRBle : public RrSensors {
   public:
    RRBle() = default;
    
    ~RRBle() = default;

    /**
     * @brief Initializes the BLE sensor interface.
     * @return 0 on success, negative value on failure.
     */
    int begin() override;

    /**
     * @brief Deinitializes the BLE sensor interface and releases resources.
     */
    void end() override;

    /**
     * @brief Reads the acceleration values from the sensor.
     * @param[out] x Reference to store the X-axis acceleration.
     * @param[out] y Reference to store the Y-axis acceleration.
     * @param[out] z Reference to store the Z-axis acceleration.
     * @return 0 on success, negative value on failure.
     */
    int readAcceleration(float& x, float& y, float& z) override;

    /**
     * @brief Checks if new acceleration data is available.
     * @return Number of available acceleration samples, or negative value on error.
     */
    int accelerationAvailable() override;

    /**
     * @brief Reads the gyroscope values from the sensor.
     * @param[out] x Reference to store the X-axis gyroscope value.
     * @param[out] y Reference to store the Y-axis gyroscope value.
     * @param[out] z Reference to store the Z-axis gyroscope value.
     * @return 0 on success, negative value on failure.
     */
    int readGyroscope(float& x, float& y, float& z) override;

    /**
     * @brief Checks if new gyroscope data is available.
     * @return Number of available gyroscope samples, or negative value on error.
     */
    int gyroscopeAvailable() override;

    /**
     * @brief Reads the magnetic field values from the sensor.
     * @param[out] x Reference to store the X-axis magnetic field value.
     * @param[out] y Reference to store the Y-axis magnetic field value.
     * @param[out] z Reference to store the Z-axis magnetic field value.
     * @return 0 on success, negative value on failure.
     */
    int readMagneticField(float& x, float& y, float& z) override;

    /**
     * @brief Checks if new magnetic field data is available.
     * @return Number of available magnetic field samples, or negative value on error.
     */
    int magneticFieldAvailable() override;
};
}  // namespace rrobot

#endif