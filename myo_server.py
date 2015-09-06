import serial
import os
import struct

if __name__ == '__main__':
    filepath = '/Users/portela/Downloads/myo-env/sdk/samples/DerivedData/hello-myo/Build/Products/Debug/myo_pose.txt'
    arduino = serial.Serial('/dev/tty.usbmodem1411', 9600)
    command_to_code = {
        'Rest': 0,
        'Fist': 1,
        'Wave In': 2,
        'Wave Out': 3,
        'Fingers Spread': 4,
        'Double Tap': 5,
        'Unknown': 6,
    }

    while True:
        if os.path.exists(filepath):
            with open(filepath) as fp:
                data = fp.read()
                if data != '':
                    arduino.write(struct.pack('!B', command_to_code[data]))

            os.remove(filepath)