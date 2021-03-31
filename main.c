//////////////////////COMMON SHARED FILE///////////////////////////////////
#include <stdlib.h>
//#include <iostream>
#include <unistd.h>
#include "Serial.h"
#include <stdio.h>
#include <fstream>
#include <cstdio>

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



	char filename[] = "temp_sensor_v.csv";
	remove(filename);


	//do {
    Antenna_to_ADC(&my);
	Short_to_ADC(&my);
    Open_to_ADC(&my);
    Hot_ambient_to_ADC(&my);
    Cable_to_ADC(&my);
    Noise_to_ADC(&my);
    VNA_to_ADC(&my);
    Antenna_to_VNA(&my);
    Short_to_VNA(&my);
    Open_to_VNA(&my);
    Match_to_VNA(&my);
    Hot_Ambient_to_VNA(&my);
    Cable_to_VNA(&my);
    Noise_to_VNA(&my);



	sleep(.1);
	float rec_number_array[MAXFLOATS];//MAXFLOATS is set to 10 in Serial.h right now
	int number_of_rec_numbers = 7;
	Get_temp_sensor_V(&my,rec_number_array,number_of_rec_numbers);
	//}while(1);
	
	//Extract Data
	//float rec_number = 0;
	//for (int i = 0;i<number_of_rec_numbers;i++) {
	//	rec_number = rec_number_array[i];	
	//	printf("Number Received = %lf \n",rec_number);
	//}
	//}
	

} //end main loop desktop computer
