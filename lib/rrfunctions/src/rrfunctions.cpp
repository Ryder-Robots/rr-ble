
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
    s = RR_ST_;
    return rrevent(MSP_NONE);
}

rrevent rrfunctions::sonar_r(rrevent e, int& s) { return rrevent(MSP_NONE); }

rrevent rrfunctions::sen_acc_r(rrevent e, int& s) { return rrevent(MSP_NONE); }

rrevent rrfunctions::sen_gyro_r(rrevent e, int& s) { return rrevent(MSP_NONE); }

rrevent rrfunctions::sen_mag_r(rrevent e, int& s) { return rrevent(MSP_NONE); }

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
    return rrevent(MSP_NONE);
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
rrevent rrfunctions::rotate_r(rrevent e, int& s) { return rrevent(MSP_NONE); }
