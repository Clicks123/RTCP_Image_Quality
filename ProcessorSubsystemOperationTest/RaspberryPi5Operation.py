from gpiozero import LED
import serial
import time

led=LED(24)
led.on()

ser = serial.Serial(
        port='/dev/serial0',
        baudrate = 9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
)
counter=0
while True:
        ser.write('Hello from Pi 5: %d\n'%(counter))
        time.sleep(1)
        counter+=1