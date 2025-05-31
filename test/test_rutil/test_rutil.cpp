#include <ArduinoFake.h>
#include <unity.h>
#include <rrutil.hpp>

using namespace rrobot;

void test_split_string(void) {
    const String s = "101;0;0;";
    String results[100];
    split_string(s, ';', results, 100);

    TEST_ASSERT_EQUAL_STRING("101", results[0].c_str());
    TEST_ASSERT_EQUAL_STRING("0", results[1].c_str());
    TEST_ASSERT_EQUAL_STRING("0", results[2].c_str());
}

int runUnityTests(void) {
    UNITY_BEGIN();
    RUN_TEST(test_split_string);
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