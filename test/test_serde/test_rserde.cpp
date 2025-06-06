#include <ArduinoFake.h>
#include <unity.h>

#include <serde.hpp>

using namespace rrobot;

void create_event(void) {
    String s[3] = {"0", "0", "0"};
    rrevent e(218, 3, s);
    TEST_ASSERT_EQUAL_INT(218, e.get_cmd());
    TEST_ASSERT_EQUAL_size_t(3, e.get_sz());
    TEST_ASSERT_EQUAL_STRING("0", e.get_data(0).c_str());
    TEST_ASSERT_EQUAL_STRING("0", e.get_data(1).c_str());
    TEST_ASSERT_EQUAL_STRING("0", e.get_data(2).c_str());
}

void deserialize_no_data(void) {
    rrevent e = serde::deserialize("218;0;0;");
    TEST_ASSERT_EQUAL_INT(218, e.get_cmd());
    TEST_ASSERT_EQUAL_INT(0, e.get_sz());
}

void deserialize_with_data(void) {
    rrevent e = serde::deserialize("218;7;0;1;1;2;3;");

    TEST_ASSERT_EQUAL_INT(218, e.get_cmd());
    TEST_ASSERT_EQUAL_INT(4, e.get_sz());
    TEST_ASSERT_EQUAL_STRING("1", e.get_data(0).c_str());
    TEST_ASSERT_EQUAL_STRING("1", e.get_data(1).c_str());
    TEST_ASSERT_EQUAL_STRING("2", e.get_data(2).c_str());
    TEST_ASSERT_EQUAL_STRING("3", e.get_data(3).c_str());
}

void serialize_with_data(void) {
    rrevent e = serde::deserialize("218;7;0;1;1;2;3;");
    String s = serde::serialize(e);

    String out = "218;8;41667;1;1;2;3;\x1E";
    TEST_ASSERT_EQUAL_STRING(out.c_str(), s.c_str());
}

int runUnityTests(void) {
    UNITY_BEGIN();
    RUN_TEST(create_event);
    RUN_TEST(deserialize_no_data);
    RUN_TEST(deserialize_with_data);
    RUN_TEST(serialize_with_data);
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