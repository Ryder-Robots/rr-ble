#include <ArduinoFake.h>
#include <unity.h>

#include <rrfunctions.hpp>

using namespace rrobot;
using namespace fakeit;

// PID variables
double setpoint = 0;
double input = 0;
double output = 0;  // Desired heading (forward)
// Current heading (from gyro)
// PID correction
// PID tuning parameters
double Kp = 1.0, Ki = 0.0, Kd = 0.05;

class MockSensors : public RrSensors {
   public:
    virtual int begin() override { return 1; }
    virtual void end() override { return; }

    virtual int readAcceleration(float& x, float& y, float& z) override {
        x = 1;
        y = 1;
        z = 0;
        return 1;
    }
    virtual int accelerationAvailable() override { return 1; }

    virtual int readGyroscope(float& x, float& y, float& z) override { return 1; }
    virtual int gyroscopeAvailable() override { return 1; }

    virtual int readMagneticField(float& x, float& y, float& z) override { return 1; }
    virtual int magneticFieldAvailable() override { return 1; }
};

void setUp(void) {
    // Reset all ArduinoFake mocks before each test
    ArduinoFakeReset();
}

void test_moveDoesSetState(void) {
    When(Method(ArduinoFake(), millis)).AlwaysReturn(1);
    PID _pid(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);
    MockSensors _ble;
    rrstate _state(_pid);
    _state.set_cstate(RR_ST_);
    rrfunctions::move_r(rrevent(RR_COMMANDS[MSP_MOVE_P]), _state, _ble);
    TEST_ASSERT_EQUAL_INT(RR_MV_, _state.get_cstate());
    TEST_ASSERT_EQUAL(rrhbridge_map::_PWM_VALUE, _state.get_ena());
    TEST_ASSERT_EQUAL(rrhbridge_map::_PWM_VALUE, _state.get_enb());
    TEST_ASSERT_EQUAL(HIGH, _state.get_in1());
    TEST_ASSERT_EQUAL(LOW, _state.get_in2());
    TEST_ASSERT_EQUAL(HIGH, _state.get_in3());
    TEST_ASSERT_EQUAL(LOW, _state.get_in4());
}

void test_noneDoesSetState(void) {
    When(Method(ArduinoFake(), millis)).AlwaysReturn(1);
    PID _pid(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);
    When(Method(ArduinoFake(), analogWrite)).AlwaysReturn();
    When(Method(ArduinoFake(), digitalWrite)).AlwaysReturn();

    MockSensors _ble;
    rrstate _state(_pid);
    _state.set_cstate(RR_MV_);
    rrfunctions::none_r(rrevent(RR_COMMANDS[MSP_NONE]), _state, _ble);
    TEST_ASSERT_EQUAL_INT(RR_ST_, _state.get_cstate());
    TEST_ASSERT_EQUAL(0, _state.get_ena());
    TEST_ASSERT_EQUAL(0, _state.get_enb());
    TEST_ASSERT_EQUAL(LOW, _state.get_in1());
    TEST_ASSERT_EQUAL(LOW, _state.get_in2());
    TEST_ASSERT_EQUAL(LOW, _state.get_in3());
    TEST_ASSERT_EQUAL(LOW, _state.get_in4());

    Verify(Method(ArduinoFake(), analogWrite).Using(rrhbridge_map::_ENA, 0)).Once();
    Verify(Method(ArduinoFake(), analogWrite).Using(rrhbridge_map::_ENB, 0)).Once();
}

void test_moveUsingArrayCall(void) {
    When(Method(ArduinoFake(), millis)).AlwaysReturn(1);
    PID _pid(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);
    MockSensors _ble;
    rrstate _state(_pid);
    _state.set_cstate(RR_ST_);
    rrevent e = rrevent(RR_COMMANDS[MSP_MOVE_P]);
    rrfunctions::_functions[POS(e.get_cmd())](e, _state, _ble);
    TEST_ASSERT_EQUAL_INT(RR_MV_, _state.get_cstate());
}

void test_heading_d(void) {
    TEST_ASSERT_EQUAL(true, (rrfunctions::heading_d(0, 1, 0) == 90));      // East
    TEST_ASSERT_EQUAL(true, (rrfunctions::heading_d(0, -1, 0) == -90));    // West
    TEST_ASSERT_EQUAL(true, (rrfunctions::heading_d(1, 0, 0) == 0));       // North
    TEST_ASSERT_EQUAL(true, (rrfunctions::heading_d(-1, 0, 0) == 180));    // South
    TEST_ASSERT_EQUAL(true, (rrfunctions::heading_d(1, 1, 0) == 45));      // North East
    TEST_ASSERT_EQUAL(true, (rrfunctions::heading_d(1, -1, 0) == -45));    // North West
    TEST_ASSERT_EQUAL(true, (rrfunctions::heading_d(-1, 1, 0) == 135));    // South East
    TEST_ASSERT_EQUAL(true, (rrfunctions::heading_d(-1, -1, 0) == -135));  // South West
}

void test_heading_d_gyro(void) {
    When(Method(ArduinoFake(), millis)).AlwaysReturn(1);
    PID _pid(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);
    rrstate _state(_pid);
    _state.set_sens(r_imu_sens::_MAG, true, 0, 1, 0);
    TEST_ASSERT_EQUAL(true, (rrfunctions::heading_d_gyro(_state) == 90));  // East

    _state.set_sens(r_imu_sens::_MAG, true, -1, 11, 0);
    TEST_ASSERT_EQUAL(true, (rrfunctions::heading_d(-1, -1, 0) == -135));  // South West
}

void test_sen_acc_s(void) {
    When(Method(ArduinoFake(), millis)).AlwaysReturn(1);
    PID _pid(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);
    rrstate _state(_pid);
    MockSensors _ble;
    _state.set_sens(r_imu_sens::_ACC, true, 0, 0, 0);
    rrfunctions::sen_acc_s(_state, _ble);
    float a = 0, x = 0, y = 0, z = 0;
    _state.get_sens(r_imu_sens::_ACC, a, x, y, z);

    TEST_ASSERT_EQUAL(1, a);
    TEST_ASSERT_EQUAL(1, x);
    TEST_ASSERT_EQUAL(1, y);
    TEST_ASSERT_EQUAL(0, z);
}

void test_rotate_r_(void) {
    When(Method(ArduinoFake(), millis)).AlwaysReturn(1);
    PID _pid(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);
    rrstate _state(_pid);
    MockSensors _ble;
    When(Method(ArduinoFake(), analogWrite)).AlwaysReturn();
    When(Method(ArduinoFake(), digitalWrite)).AlwaysReturn();

    // set compass to north
    _state.set_sens(r_imu_sens::_MAG, 1, 1, 0, 0);

    // Rotate the drone to face east.
    String data[] = {"1", "0", "1", "0"};
    rrevent e(RR_COMMANDS[MSP_ROTATE_P], 4, data);
    rrfunctions::rotate_r(e, _state, _ble);
}

void test_rotate_r(void) {}

int runUnityTests(void) {
    UNITY_BEGIN();
    RUN_TEST(test_moveDoesSetState);
    RUN_TEST(test_noneDoesSetState);
    RUN_TEST(test_moveUsingArrayCall);
    RUN_TEST(test_heading_d);
    RUN_TEST(test_heading_d_gyro);
    RUN_TEST(test_sen_acc_s);
    RUN_TEST(test_rotate_r);
    return UNITY_END();
}

#ifdef ARDUINO
void setup() {
    delay(2000);
    runUnityTests();
}

void loop() {}
#else
int main(void) { return runUnityTests(); }
#endif
