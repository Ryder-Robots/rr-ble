#include <ArduinoFake.h>
#include <unity.h>

#include <rrfunctions.hpp>

using namespace rrobot;

void test_moveDoesSetState(void) {
    int _state = RR_ST_;
    rrfunctions::move_r(rrevent(RR_COMMANDS[MSP_MOVE_P]), _state);
    TEST_ASSERT_EQUAL_INT(RR_MV_, _state);
}

void test_noneDoesSetState(void) {
    int _state = RR_ST_;
    rrfunctions::none_r(rrevent(RR_COMMANDS[MSP_NONE]), _state);
    TEST_ASSERT_EQUAL_INT(RR_ST_, _state);
}

int runUnityTests(void) {
    UNITY_BEGIN();
    RUN_TEST(test_moveDoesSetState);
    RUN_TEST(test_noneDoesSetState);
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
