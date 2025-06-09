# rr-ble
BLE interface

This documentation describes the Arduino Nano BLE implementation for the Ryder Robots project. The firmware provides a serial interface over USB, allowing communication with the `librrobot` library, which is typically run on a Raspberry Pi 4 or 4B. This setup enables seamless integration between the Arduino Nano BLE and the robot's main control system.

# External CLI Test
```
python3 -m venv .venv
source ./.venv/bin/activate
pip3 install pyserial

```