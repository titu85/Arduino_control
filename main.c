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
	my = SerialInit("/dev/ttyACM0",115200); 

	//Wait 5 seconds because for some reason the Arduino reboots when you 
	//run this code
	//https://playground.arduino.cc/Main/DisablingAutoResetOnSerialConnection/
	printf("Sleeping for 5 seconds to let the Arduino Reboot \n");
	sleep(5);



	char filename[] = "temp_sensor_v.csv";
	remove(filename);


	do {
    	Antenna_to_ADC(&my); //connect antenna to digitizer #U6Rf1--U9Rf1
        //Short_to_ADC(&my); //connect Short to digitizer #U6Rf2--U9Rf1
        //Open_to_ADC(&my);//connect open to digitizer #U6Rf3--U9Rf1
		//Match_to_ADC(&my);//connect Match to digitizer #U5Rf1--U9Rf1
        //Hot_ambient_to_ADC(&my);//connect Hotload to digitizer #U6Rf3--U9Rf1
        //Cable_to_ADC(&my);//connect Cable to digitizer #U5Rf3--U9Rf1
        //Noise_to_ADC(&my);//connect Noise to digitizer #U5Rf4--U9Rf1
        //VNA_to_ADC(&my);//connect VNA to digitizer #U8Rfc--U9Rf
		sleep(1);
        //Antenna_to_VNA(&my);//connect Antenna to VNA #U8Rfc--U8Rfc
        //Short_to_VNA(&my);//connect Short to VNA #U6Rf2--U8Rfc
        //Open_to_VNA(&my);//connect Open to VNA #U6Rf3--U8Rfc
        Match_to_VNA(&my);//connect Match to VNA #U5Rf1--U8Rfc
        //Hot_Ambient_to_VNA(&my);//connect Hotload to VNA #U5Rf2--U8Rfc
        //Cable_to_VNA(&my);//connect cable to VNA #U5Rf3--U8Rfc
        //Noise_to_VNA(&my);//connect Noise to VNA #U5Rf4--U8Rfc



	    sleep(1);
	    float rec_number_array[MAXFLOATS];//MAXFLOATS is set to 10 in Serial.h right now
	    int number_of_rec_numbers = 7;
	    Get_temp_sensor_V(&my,rec_number_array,number_of_rec_numbers);
	}while(1);
	
	

} //end main loop desktop computer
