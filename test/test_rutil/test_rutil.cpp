#include <ArduinoFake.h>
#include <unity.h>
#include <rrblemappings.hpp>
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

void test_binary_search(void) { 
    TEST_ASSERT_EQUAL_INT(MSP_SONAR_ALTITUDE_P, binary_search(RR_COMMANDS, RR_CMDSZ, RR_COMMANDS[MSP_SONAR_ALTITUDE_P]));
    TEST_ASSERT_EQUAL_INT(MSP_SENSOR_ACC_P, binary_search(RR_COMMANDS, RR_CMDSZ, RR_COMMANDS[MSP_SENSOR_ACC_P]));
    TEST_ASSERT_EQUAL_INT(MSP_SENSOR_GYRO_P, binary_search(RR_COMMANDS, RR_CMDSZ, RR_COMMANDS[MSP_SENSOR_GYRO_P]));
    TEST_ASSERT_EQUAL_INT(MSP_SENSOR_MAG_P, binary_search(RR_COMMANDS, RR_CMDSZ, RR_COMMANDS[MSP_SENSOR_MAG_P]));
    TEST_ASSERT_EQUAL_INT(MSP_ROTATE_P, binary_search(RR_COMMANDS, RR_CMDSZ, RR_COMMANDS[MSP_ROTATE_P]));
    TEST_ASSERT_EQUAL_INT(MSP_STOP_P, binary_search(RR_COMMANDS, RR_CMDSZ, RR_COMMANDS[MSP_STOP_P]));
    TEST_ASSERT_EQUAL_INT(MSP_MOVE_P, binary_search(RR_COMMANDS, RR_CMDSZ, RR_COMMANDS[MSP_MOVE_P]));
}

int runUnityTests(void) {
    UNITY_BEGIN();
    RUN_TEST(test_split_string);
    RUN_TEST(test_binary_search);
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