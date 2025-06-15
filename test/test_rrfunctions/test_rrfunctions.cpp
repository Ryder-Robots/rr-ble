#include <ArduinoFake.h>
#include <unity.h>

#include <rrfunctions.hpp>

using namespace rrobot;
using namespace fakeit;

void test_moveDoesSetState(void) {
    rrstate _state;
    _state.set_cstate(RR_ST_);
    rrfunctions::move_r(rrevent(RR_COMMANDS[MSP_MOVE_P]), _state);
    TEST_ASSERT_EQUAL_INT(RR_MV_, _state.get_cstate());
}

void test_noneDoesSetState(void) {
    When(Method(ArduinoFake(), analogWrite)).AlwaysReturn();
    When(Method(ArduinoFake(), digitalWrite)).AlwaysReturn();

    rrstate _state;
    _state.set_cstate(RR_MV_);
    rrfunctions::none_r(rrevent(RR_COMMANDS[MSP_NONE]), _state);
    TEST_ASSERT_EQUAL_INT(RR_ST_, _state.get_cstate());

    Verify(Method(ArduinoFake(), analogWrite).Using(rrhbridge_map::_ENA, 0)).Once();
    Verify(Method(ArduinoFake(), analogWrite).Using(rrhbridge_map::_ENB, 0)).Once();
}

void test_moveUsingArrayCall(void) {
    rrstate _state;
    _state.set_cstate(RR_ST_);
    rrevent e = rrevent(RR_COMMANDS[MSP_MOVE_P]);
    rrfunctions::_functions[POS(e.get_cmd())](e, _state);
    TEST_ASSERT_EQUAL_INT(RR_MV_, _state.get_cstate());
}

int runUnityTests(void) {
    UNITY_BEGIN();
    RUN_TEST(test_moveDoesSetState);
    RUN_TEST(test_noneDoesSetState);
    RUN_TEST(test_moveUsingArrayCall);
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
