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
rrevent rrfunctions::none_r(rrevent e, rrstate& s, RrSensors& b) {
    stop_r(rrevent(POS(MSP_STOP_P)), s, b);
    return rrevent(MSP_NONE);
}

rrevent rrfunctions::sonar_r(rrevent e, rrstate& s, RrSensors& b) { return rrevent(MSP_NONE, 2, rrerror::err_noimp); }

bool rrfunctions::sen_acc_s(rrstate& s, RrSensors& b) {
    float x = 0, y = 0, z = 0;
    if (!b.accelerationAvailable()) {
        return false;
    }
    b.readAcceleration(x, y, z);
    s.set_sens(r_imu_sens::_ACC, true, x, y, z);
    return true;
}

bool rrfunctions::sen_gyro_s(rrstate& s, RrSensors& b) {
    float x = 0, y = 0, z = 0;
    if (!b.gyroscopeAvailable()) {
        return false;
    }
    b.readGyroscope(x, y, z);
    s.set_sens(r_imu_sens::_GYRO, true, x, y, z);
    return true;
}

bool rrfunctions::sen_mag_s(rrstate& s, RrSensors& b) {
    float x = 0, y = 0, z = 0;
    if (!b.magneticFieldAvailable()) {
        return false;
    }
    b.readMagneticField(x, y, z);
    s.set_sens(r_imu_sens::_MAG, true, x, y, z);
    return true;
}

bool rrfunctions::move_s(rrstate& s, RrSensors& b) {
    analogWrite(rrhbridge_map::_ENA, s.get_ena());
    analogWrite(rrhbridge_map::_ENB, s.get_enb());
    digitalWrite(rrhbridge_map::_IN1, s.get_in1());
    digitalWrite(rrhbridge_map::_IN2, s.get_in2());
    digitalWrite(rrhbridge_map::_IN3, s.get_in3());
    digitalWrite(rrhbridge_map::_IN4, s.get_in4());
    s.set_cstate(RR_MV_);
    return true;
}

bool rrfunctions::stop_s(rrstate& s, RrSensors& b) {
    s.set_ena(0);
    s.set_enb(0);
    s.set_in1(LOW);
    s.set_in2(LOW);
    s.set_in3(LOW);
    s.set_in4(LOW);
    move_s(s, b);
    s.set_cstate(RR_ST_);
    return true;
}

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
rrevent rrfunctions::sen_acc_r(rrevent e, rrstate& s, RrSensors& b) {
    if (!sen_acc_s(s, b)) {
        return rrevent(MSP_NONE, 2, rrerror::err_noimu);
    }
    float a = 0, x = 0, y = 0, z = 0;
    s.get_sens(r_imu_sens::_ACC, a, x, y, z);
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
rrevent rrfunctions::sen_gyro_r(rrevent e, rrstate& s, RrSensors& b) {
    if (!sen_gyro_s(s, b)) {
        return rrevent(MSP_NONE, 2, rrerror::err_noimu);
    }
    float a = 0, x = 0, y = 0, z = 0;
    s.get_sens(r_imu_sens::_GYRO, a, x, y, z);
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
rrevent rrfunctions::sen_mag_r(rrevent e, rrstate& s, RrSensors& b) {
    if (!sen_mag_s(s, b)) {
        return rrevent(MSP_NONE, 2, rrerror::err_noimu);
    }
    float a = 0, x = 0, y = 0, z = 0;
    s.get_sens(r_imu_sens::_MAG, a, x, y, z);
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
rrevent rrfunctions::stop_r(const rrevent e, rrstate& s, RrSensors& b) {
    if (s.get_cstate() != RR_ST_) {
        stop_s(s, b);
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
rrevent rrfunctions::move_r(const rrevent e, rrstate& s, RrSensors& b) {
    if (s.get_cstate() != RR_MV_) {
        s.set_cstate(RR_MV_);

        // PWM values will need max and min, for the PID algorithm once implmented.
        s.set_ena(rrhbridge_map::_PWM_VALUE);
        s.set_enb(rrhbridge_map::_PWM_VALUE);
        s.set_in1(HIGH);
        s.set_in2(LOW);
        s.set_in3(HIGH);
        s.set_in4(LOW);
    }
    String vout[] = {
        String(s.get_ena()), String(s.get_enb()), String(s.get_in1()),
        String(s.get_in2()), String(s.get_in3()), String(s.get_in4()),
    };
    rrevent out = rrevent(RR_COMMANDS[MSP_MOVE_P], 6, vout);
    return out;
}

int rrfunctions::heading_d(float x, float y, float z) {
    int d = DG(atan2(y, x));
    return d;
}

float rrfunctions::heading_d_gyro(rrstate& s) {
    float a = 0, x = 0, y = 0, z = 0;
    s.get_sens(r_imu_sens::_MAG, a, x, y, z);
    return heading_d(x, y, z);
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
rrevent rrfunctions::rotate_r(rrevent e, rrstate& s, RrSensors& b) {
    sen_mag_s(s, b);
    float heading = heading_d_gyro(s),
          new_heading = heading_d(atof(e.get_data(r_imu_po::_X_P).c_str()), atof(e.get_data(r_imu_po::_Y_P).c_str()),
                                  atof(e.get_data(r_imu_po::_Z_P).c_str())),
          i1 = heading, i2 = new_heading;

    if (heading < new_heading) {
        i1 = new_heading, i2 = heading;
        s.set_in1(LOW);
        s.set_in2(HIGH);
        s.set_in3(HIGH);
        s.set_in4(LOW);
    } else if (heading > new_heading) {
        s.set_in1(HIGH);
        s.set_in2(LOW);
        s.set_in3(LOW);
        s.set_in4(HIGH);
    }

    while (i1 > i2) {
        move_s(s, b);
        delay(50);
        sen_mag_s(s, b);
        heading = heading_d_gyro(s);

        if (heading < new_heading) {
            i1 = new_heading, i2 = heading;
        } else {
            i2 = new_heading, i1 = heading;
        }
    }
    String vout[] = {
        String(s.get_ena()), String(s.get_enb()), String(s.get_in1()),
        String(s.get_in2()), String(s.get_in3()), String(s.get_in4()),
    };
    stop_s(s, b);
    s.set_cstate(RR_RT_);
    return rrevent(MSP_ROTATE_P, 6, vout);
}
