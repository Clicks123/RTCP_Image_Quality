from gpiozero import led
import serial
import time

led=LED(24)
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
    ser.write("Hello from Pi 5\n")
    time.sleep(1)