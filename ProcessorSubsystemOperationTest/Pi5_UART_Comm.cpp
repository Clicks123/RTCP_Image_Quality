#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include "UARTcomm.h"

int Pi5UART(void){
    int serial_port = open("/dev/serial0", O_RDWR);

    // Check for errors
    if (serial_port < 0)
    {
        printf("Error %i from open: %s\n", errno, strerror(errno));
    }

    struct termios tty;

    // Read settings and check for errors
    if (tcgetattr(serial_port, &tty) != 0)
    {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    }

    // Setting tty's settings
    // Control modes
    tty.c_cflag &= ~PARENB;          // Clear parity bit
    tty.c_cflag &= ~CSTOPB;          // Clear stop bit, only 1 stop bit used
    tty.c_cflag &= ~CSIZE;           // Clear size bits
    tty.c_cflag |= CS8;              // 8 bits per byte
    tty.c_cflag &= ~CRTSCTS;         // Disable RTS/CTS hardware flow control
    tty.c_cflag |= (CREAD | CLOCAL); // Turn on READ and ignore control lines

    // Local modes
    tty.c_lflag &= ~ICANON; // Disable cannonical mode
    tty.c_lflag &= ~ECHO;   // Disable echo
    tty.c_lflag &= ~ECHOE;  // Disable erasure
    tty.c_lflag &= ~ECHONL; // Disable new-line echo
    tty.c_lflag &= ~ISIG;   // Disable interpretation of INTR, QUIT and SUSP

    // Output modes
    tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes
    tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed

    // Baud rate
    cfsetispeed(&tty, B9600); // Input baud rate of 9600
    cfsetospeed(&tty, B9600); // Output baud rate of 9600

    // Save tty settings, also checking for error
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0)
    {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
    }

    // Send a message
    unsigned char msg[] = "Hello from Pi 5";
    while (1)
    {
        write(serial_port, msg, sizeof(msg));
    }

    return 0;
}