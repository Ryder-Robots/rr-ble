#include <ArduinoFake.h>
#include <unity.h>

#include <rrobot.hpp>

using namespace rrobot;

void create_event(void) {
    String s[3] = {"0", "0", "0"};
    rrevent e(218, 3, s);
    TEST_ASSERT_EQUAL_INT(218, e.get_cmd());
    TEST_ASSERT_EQUAL_size_t(3, e.get_sz());
    TEST_ASSERT_EQUAL_INT(0, e.get_data()[0].equals("0"));
    TEST_ASSERT_EQUAL_INT(0, e.get_data()[1].equals("0"));
    TEST_ASSERT_EQUAL_INT(0, e.get_data()[2].equals("0"));
}

int runUnityTests(void) {
    UNITY_BEGIN();
    RUN_TEST(create_event);
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