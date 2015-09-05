import serial
import os
import struct

if __name__ == '__main__':
    filepath = '/Users/portela/Downloads/myo-env/sdk/samples/DerivedData/hello-myo/Build/Products/Debug/myo_pose.txt'
    arduino = serial.Serial('/dev/tty.usbmodem1411', 9600)

    while True:
        if os.path.exists(filepath):
            with open(filepath) as fp:
                data = fp.read()

                if data == 'Fist':
                  arduino.write(struct.pack('!B', 1))
                elif data == 'Wave In':
                  arduino.write(struct.pack('!B', 2))
                elif data == 'Wave Out':
                  arduino.write(struct.pack('!B', 3))

            os.remove(filepath)