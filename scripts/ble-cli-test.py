import serial

port_name = '/dev/cu.usbmodem23201'
baud_rate = 9600

try:
    # Open serial port with 9600 8-N-1 (defaults)
    ser = serial.Serial(port_name, baud_rate, timeout=1)

    commands = ["58", "216", "217", "218", "220", "221"];
    for cmd in commands:
        command_str = f"{cmd};0;0;0;\x1E"
        ser.write(command_str.encode('utf-8'))
        response = ser.read(100)
        print(f"Received: {response.decode('utf-8', errors='ignore')}")


    # command_str = "217;0;0;0;\x1E"
    # ser.write(command_str.encode('utf-8'))
    # response = ser.read(100)
    # print(f"Received: {response.decode('utf-8', errors='ignore')}")

    ser.close()
except Exception as e:
    print(f"Error: {e}")
