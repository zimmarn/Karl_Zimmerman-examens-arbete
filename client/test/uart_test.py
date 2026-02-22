import time
import serial

BAUD = 2097152
PORT = "/dev/ttyUSB0"  

ser = serial.Serial(PORT, BAUD)

print("test started")


while True:
    tx = (b'2356623451' * 300)

    print("Sent:", tx)
    ser.write(tx)
    rx = ser.read(300)
    if rx:
        print("Received:", rx)
    else:
        print("Timeout / no data")
    print(tx == rx)
    time.sleep(10)