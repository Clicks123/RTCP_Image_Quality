#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include "UARTcomm.h"

int main(int arg){
    if(arg==1){
        Pi5UART();
    }

    else if(arg==2){
        ZeroWUART();
    }

    else{
        printf("Error\n");
    }

    return 0;
}