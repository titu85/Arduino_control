//////////////////////COMMON SHARED FILE///////////////////////////////////
#include <stdlib.h>
//#include <iostream>
#include <unistd.h>
#include "Serial.h"
#include <stdio.h>

////////////////////////DESKTOP COMPUTER///////////////////////////////////
int main() {
	//Initialize Serial Port
	//using this baudrate
	printf("Initializing the dev Port \n");
	//Make sure Arduino is on this port
	//If this doesn't work even if you are sure that you have the right port.
	//Try manually sending w/r (carriage return) via the Arduino Serial monitor
	//To be sure that Serial communication is actually working 
	my = SerialInit("/dev/ttyACM0",115200); 

	//Wait 5 seconds because for some reason the Arduino reboots when you 
	//run this code
	//https://playground.arduino.cc/Main/DisablingAutoResetOnSerialConnection/
	printf("Sleeping for 5 seconds to let the Arduino Reboot \n");
	sleep(5);

	//Send w\r to Arduino
	//SerialPutHello(&my,1);

	//Consume w\r\n
	//SerialGetHello(&my,1);
    
	SerialPutc(&my,'1');
    for (int i = 0;i<2;i++) {
	int echo;
	int err = 0;
    char inchar;
    inchar = SerialGetc(&my);
    int val = int(inchar);
      //  err+=val;
       // if (echo) {
    printf("%c \n",inchar);
	//printf("val%d \n",val);
      //  }
	}
	

} //end main loop desktop computer
