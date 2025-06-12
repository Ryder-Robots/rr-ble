
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
rrevent rrfunctions::none_r(rrevent e, rrstate& s) {
    stop_r(rrevent(POS(MSP_STOP_P)), s);
    return rrevent(MSP_NONE);
}

rrevent rrfunctions::sonar_r(rrevent e, rrstate& s) { return rrevent(MSP_NONE, 2, rrerror::err_noimp); }

/**
 * @brief Handles the accelometer sensor event for the robot.
 *
 * This function reads the accelometer data from the IMU sensor if available.
 * It retrieves the X, Y, and Z components of the accelometer and packages them
 * into a response event. If the accelometer data is not available, it returns
 * an event indicating no operation.
 *
 * @param e The input event that triggered the accelometer sensor reading.
 * @param s Reference to the state variable (unused in this function).
 * @return rrevent An event containing the accelometer  sensor data if available,
 *                 or an event indicating no operation (MSP_NONE) if not available.
 */
rrevent rrfunctions::sen_acc_r(rrevent e, rrstate& s) {
    float x = 0, y = 0, z = 0;
    if (!IMU.accelerationAvailable()) {
        return rrevent(MSP_NONE, 2, rrerror::err_noimu);
    }
    IMU.readAcceleration(x, y, z);
    String data[4] = {String(1), String(x, 2), String(y, 2), String(z, 2)};
    rrevent r = rrevent(RR_COMMANDS[MSP_SENSOR_ACC_P], 4, data);
    return r;
}

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
rrevent rrfunctions::sen_gyro_r(rrevent e, rrstate& s) {
    float x = 0, y = 0, z = 0;
    if (!IMU.gyroscopeAvailable()) {
        return rrevent(MSP_NONE, 2, rrerror::err_noimu);
    }
    IMU.readGyroscope(x, y, z);
    String data[4] = {String(1), String(x, 2), String(y, 2), String(z, 2)};
    rrevent r = rrevent(RR_COMMANDS[MSP_SENSOR_GYRO_P], 4, data);
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
rrevent rrfunctions::sen_mag_r(rrevent e, rrstate& s) {
    float x = 0, y = 0, z = 0;
    if (!IMU.magneticFieldAvailable()) {
        return rrevent(MSP_NONE, 2, rrerror::err_noimu);
    }
    IMU.readMagneticField(x, y, z);
    x = _UT_SCALED(x), y = _UT_SCALED(y), z = _UT_SCALED(z);
    String data[4] = {String(1), String(x, 2), String(y, 2), String(z, 2)};
    rrevent r = rrevent(RR_COMMANDS[MSP_SENSOR_MAG_P], 4, data);
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
rrevent rrfunctions::stop_r(const rrevent e, rrstate& s) {
    if (s.get_cstate() != RR_ST_) {
        s.set_cstate(RR_ST_);
        rrfunctions::move_t(s, 0, 0, LOW, LOW, LOW, LOW);
    }
    String vout[] = {
        String(s.get_ena()), String(s.get_enb()), String(s.get_in1()),
        String(s.get_in2()), String(s.get_in3()), String(s.get_in4()),
    };
    rrevent out = rrevent(RR_COMMANDS[MSP_STOP_P], 6, vout);
    return out;
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
rrevent rrfunctions::move_r(const rrevent e, rrstate& s) {
    if (s.get_cstate() != RR_MV_) {
        s.set_cstate(RR_MV_);
        rrfunctions::move_t(s, rrhbridge_map::_PWM_VALUE, rrhbridge_map::_PWM_VALUE, HIGH, LOW, HIGH, LOW);
    }
    String vout[] = {
        String(s.get_ena()), String(s.get_enb()), String(s.get_in1()),
        String(s.get_in2()), String(s.get_in3()), String(s.get_in4()),
    };
    rrevent out = rrevent(RR_COMMANDS[MSP_STOP_P], 6, vout);
    return out;
}

void rrfunctions::move_t(rrstate& s, int ena, int enb, int in1, int in2, int in3, int in4) {
    analogWrite(rrhbridge_map::_ENA, ena);
    analogWrite(rrhbridge_map::_ENB, enb);
    digitalWrite(rrhbridge_map::_IN1, in1);
    digitalWrite(rrhbridge_map::_IN2, in2);
    digitalWrite(rrhbridge_map::_IN3, in3);
    digitalWrite(rrhbridge_map::_IN4, in4);

    s.set_ena(ena);
    s.set_enb(enb);
    s.set_in1(in1);
    s.set_in2(in2);
    s.set_in3(in3);
    s.set_in4(in4);
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
rrevent rrfunctions::rotate_r(rrevent e, rrstate& s) { return rrevent(MSP_NONE, 2, rrerror::err_noimp); }
