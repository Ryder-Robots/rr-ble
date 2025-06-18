#include <ArduinoFake.h>
#include <unity.h>

#include <rrfunctions.hpp>

using namespace rrobot;
using namespace fakeit;

class MockSensors : public RrSensors {
   public:
    int begin() override { return 1; }
    void end() override { return; }

    int readAcceleration(float& x, float& y, float& z) override { return 1; }
    int accelerationAvailable() override { return 1; }

    int readGyroscope(float& x, float& y, float& z) override { return 1; }
    int gyroscopeAvailable() override { return 1; }

    int readMagneticField(float& x, float& y, float& z) override { return 1; }
    int magneticFieldAvailable() override { return 1; }
};

void setUp(void) {
    // Reset all ArduinoFake mocks before each test
    ArduinoFakeReset();
}

void test_moveDoesSetState(void) {
    MockSensors _ble;
    rrstate _state;
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
    When(Method(ArduinoFake(), analogWrite)).AlwaysReturn();
    When(Method(ArduinoFake(), digitalWrite)).AlwaysReturn();

    MockSensors _ble;
    rrstate _state;
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
    MockSensors _ble;
    rrstate _state;
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
    rrstate _state;
    _state.set_sens(r_imu_sens::_MAG, true, 0, 1, 0);
    TEST_ASSERT_EQUAL(true, (rrfunctions::heading_d_gyro(_state) == 90));  // East

    _state.set_sens(r_imu_sens::_MAG, true, -1, 11, 0);
    TEST_ASSERT_EQUAL(true, (rrfunctions::heading_d(-1, -1, 0) == -135));  // South West
}

int runUnityTests(void) {
    UNITY_BEGIN();
    RUN_TEST(test_moveDoesSetState);
    RUN_TEST(test_noneDoesSetState);
    RUN_TEST(test_moveUsingArrayCall);
    RUN_TEST(test_heading_d);
    RUN_TEST(test_heading_d_gyro);
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
