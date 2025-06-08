
#include <rrfunctions.hpp>

using namespace rrobot;

/**
 * @brief Handles the 'none' event, typically invoked during error conditions.
 *
 * This method is called when the robot encounters an error state,  It resets the state variable to
 * the default stop state and returns an event indicating no operation should be performed.
 *
 * @param e The input event that triggered the error handling.
 * @param s Reference to the state variable, which will be set to the stop state (RR_ST_).
 * @return rrevent An event indicating no operation (MSP_NONE).
 */
// Does the same thing as stop. if the robot ever has any red flashing light though
// to indicate something went wrong this would be where we would trigger then :)
rrevent rrfunctions::none_r(rrevent e, int& s) {
    stop_r(rrevent(POS(MSP_STOP_P)), s);
    return rrevent(MSP_NONE);
}

rrevent rrfunctions::sonar_r(rrevent e, int& s) { return rrevent(MSP_NONE); }

rrevent rrfunctions::sen_acc_r(rrevent e, int& s) { return rrevent(MSP_NONE); }

/**
 * @brief Handles the gyroscope sensor event for the robot.
 *
 * This function reads the gyroscope data from the IMU sensor if available.
 * It retrieves the X, Y, and Z components of the gyroscope and packages them
 * into a response event. If the gyroscope data is not available, it returns
 * an event indicating no operation.
 *
 * @param e The input event that triggered the gyroscope sensor reading.
 * @param s Reference to the state variable (unused in this function).
 * @return rrevent An event containing the gyroscope  sensor data if available,
 *                 or an event indicating no operation (MSP_NONE) if not available.
 */
rrevent rrfunctions::sen_gyro_r(rrevent e, int& s) {
    float x = 0, y = 0, z = 0;
    if (!IMU.gyroscopeAvailable()) {
        return rrevent(MSP_NONE);
    }
    IMU.readGyroscope(x, y, z);
    String data[4] = {String(1), String(x, 2), String(y, 2), String(z, 2)};
    rrevent r = rrevent(POS(MSP_SENSOR_GYRO_P), 4, data);
    return r;
}

/**
 * @brief Handles the magnetic field sensor event for the robot.
 *
 * This function reads the magnetic field data from the IMU sensor if available.
 * It retrieves the X, Y, and Z components of the magnetic field and packages them
 * into a response event. If the magnetic field data is not available, it returns
 * an event indicating no operation.
 *
 * @param e The input event that triggered the magnetic field sensor reading.
 * @param s Reference to the state variable (unused in this function).
 * @return rrevent An event containing the magnetic field sensor data if available,
 *                 or an event indicating no operation (MSP_NONE) if not available.
 */
rrevent rrfunctions::sen_mag_r(rrevent e, int& s) {
    float x = 0, y = 0, z = 0;
    if (!IMU.magneticFieldAvailable()) {
        return rrevent(MSP_NONE);
    }
    IMU.readMagneticField(x, y, z);
    String data[4] = {String(1), String(x, 2), String(y, 2), String(z, 2)};
    rrevent r = rrevent(POS(MSP_SENSOR_MAG_P), 4, data);
    return r;
}

/**
 * @brief Handles the stop event for the robot.
 *
 * This method sets the state variable to indicate a move operation and returns
 * an event indicating that a stop should be performed. It is typically called
 * when a stop command is received and prepares the system to execute the stop.
 *
 * @param e The input event triggering the move.
 * @param s Reference to the state variable to be updated for move operation.
 * @return rrevent An event indicating a move should be performed (MSP_MOVE_P).
 */
rrevent rrfunctions::stop_r(rrevent e, int& s) {
    s = RR_ST_;
    if (s != RR_ST_) {
        s = RR_ST_;
    }
    // place motor in stop state after action completed.
    analogWrite(rrhbridge_map::_ENA, 0);
    analogWrite(rrhbridge_map::_ENB, 0);
    digitalWrite(rrhbridge_map::_IN1, LOW);
    digitalWrite(rrhbridge_map::_IN2, LOW);
    digitalWrite(rrhbridge_map::_IN3, LOW);
    digitalWrite(rrhbridge_map::_IN4, LOW);
    return rrevent(POS(MSP_STOP_P));
}

/**
 * @brief Handles the move event for the robot.
 *
 * This method sets the state variable to indicate a move operation and returns
 * an event indicating that a move should be performed. It is typically called
 * when a move command is received and prepares the system to execute the move.
 *
 * @param e The input event triggering the move.
 * @param s Reference to the state variable to be updated for move operation.
 * @return rrevent An event indicating a move should be performed (MSP_MOVE_P).
 */
rrevent rrfunctions::move_r(const rrevent e, int& s) {
    // load a trigger for move.
    s = RR_MV_;
    rrevent out = rrevent(RR_COMMANDS[MSP_MOVE_P]);
    return out;
}

/**
 * @brief Handles the rotation event for the robot.
 *
 * This method is intended to process rotation commands for the robot. When invoked,
 * it should update the robot's state to reflect a rotation operation and return an
 * event indicating that a rotation should be performed. Currently, this function is
 * a placeholder and does not implement any rotation logic.
 *
 * @param e The input event that triggers the rotation handling.
 * @param s Reference to the state variable, which should be updated for rotation.
 * @return rrevent An event indicating the result of the rotation handling (currently MSP_NONE).
 */
rrevent rrfunctions::rotate_r(rrevent e, int& s) {
    stop_r(POS(MSP_STOP_P), s);
    rrevent mag = sen_gyro_r(rrevent(POS(MSP_SENSOR_MAG_P)), s);

    // rotate vector 1 to be equal to v2
    // rotate right 0b1001
    if (e.get_data(r_imu_po::_X_P).toFloat() > mag.get_data(r_imu_po::_X_P).toFloat()) {
        digitalWrite(rrhbridge_map::_IN1, HIGH);
        digitalWrite(rrhbridge_map::_IN2, LOW);
        digitalWrite(rrhbridge_map::_IN3, LOW);
        digitalWrite(rrhbridge_map::_IN4, HIGH);
    }
    // rotate left 0b0110
    else {
        digitalWrite(rrhbridge_map::_IN1, LOW);
        digitalWrite(rrhbridge_map::_IN2, HIGH);
        digitalWrite(rrhbridge_map::_IN3, HIGH);
        digitalWrite(rrhbridge_map::_IN4, LOW);
    }
    // limit precision to two decimal places, to avoid under and over rotations.
    float xin = atof(e.get_data(r_imu_po::_X_P).c_str()), xout = atof(mag.get_data(r_imu_po::_X_P).c_str());

    // TODO: it just has to be opposite of what it was. dont think they'll ever be truly equal,
    while (xin != xout) {
        analogWrite(rrhbridge_map::_ENA, rrhbridge_map::_PWM_VALUE);
        analogWrite(rrhbridge_map::_ENB, rrhbridge_map::_PWM_VALUE);

        // check every 50 milliseconds.
        delay(50);
        rrevent mag = sen_gyro_r(rrevent(POS(MSP_SENSOR_MAG_P)), s);
        xout = atof(mag.get_data(r_imu_po::_X_P).c_str());
    }

    // using event rotate robot to values of mag.
    stop_r(POS(MSP_STOP_P), s);
    return rrevent(POS(MSP_ROTATE_P));
}

/**
 * @brief Executes a forward movement operation for the robot.
 *
 * This function sets the robot's state to indicate a move operation and configures
 * the H-bridge motor driver to drive both motors forward. It sets the appropriate
 * PWM values and digital signals to the motor control pins to achieve forward motion.
 *
 * @param s Reference to the state variable. If not already set to the move state (RR_MV_),
 *          it will be updated accordingly.
 */
// forward is 0b1010
void move_t(int& s) {
    if (s != RR_MV_) {
        s = RR_MV_;
    }
    analogWrite(rrhbridge_map::_ENA, rrhbridge_map::_PWM_VALUE);
    analogWrite(rrhbridge_map::_ENB, rrhbridge_map::_PWM_VALUE);
    digitalWrite(rrhbridge_map::_IN1, HIGH);
    digitalWrite(rrhbridge_map::_IN2, LOW);
    digitalWrite(rrhbridge_map::_IN3, HIGH);
    digitalWrite(rrhbridge_map::_IN4, LOW);
}
