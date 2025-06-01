#include <ArduinoFake.h>
#include <unity.h>

#include <rringress.hpp>

int runUnityTests(void) {
    UNITY_BEGIN();
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