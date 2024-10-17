from gpiozero import LED
import serial
import time

led=LED(17)
led.on()

ser = serial.Serial(
        port='/dev/ttyS0',
        baudrate = 9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
)

while True:
    x=ser.readline()
    print(x)
    time.sleep(1)