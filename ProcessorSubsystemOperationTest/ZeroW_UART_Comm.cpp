#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>

int main1(void){
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

    // Input modes
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);                                      // Turn off software flow control
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL); // Disable any special handling of received bytes

    // Frequency of read() function call
    tty.c_cc[VTIME] = 0; // No delay
    tty.c_cc[VMIN] = 1;  // Wait for at least 1 byte to be received before returning

    // Baud rate
    cfsetispeed(&tty, B9600); // Input baud rate of 9600
    cfsetospeed(&tty, B9600); // Output baud rate of 9600

    // Save tty settings, also checking for error
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0)
    {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
    }

    // Read the serial port
    char read_buf[256]; // Allocating memory for read buffer

    int n = read(serial_port, &read_buf, sizeof(read_buf)); // Number of bytes read

    // Check for errors
    if (n < 0)
    {
        printf("Error reading: %s", strerror(errno));
    }

    while (1)
    {
        printf("Message received: %c\n", read_buf);
    }

    return 0;
}