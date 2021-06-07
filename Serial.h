#ifndef SERIAL_H
#define SERIAL_H

#include <stdio.h>
//#include <iostream>

// Flow control flags
#define FC_DTRDSR       0x01
#define FC_RTSCTS       0x02
#define FC_XONXOFF      0x04
 
// variables used with the com port
#ifdef __WIN32__
//Windows needs some extra stuff
#include <conio.h>
#include <windows.h>
DCB dcb;
COMMTIMEOUTS CommTimeouts;
DWORD iBytesWritten;
DWORD iBytesRead;
bool bPortReady;
bool bWriteRC;
bool bReadRC;
#endif
//Linux just needs to open a file to write to Serial
#if defined __linux__ || __APPLE__
//So this is kind of a hack but basically I change HANDLE to FILE so that 
//I can use the exact same function declarations for Linux
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#define HANDLE int //this is my hack that I've done so that I can use windows commands on linux
#endif

#ifdef RPI
//sudo apt-get install wiringpi
#include <wiringPi.h>
#include <wiringSerial.h>

//to compile run
//g++ -o run.exe Telemetry.cpp -lwiringPi (this is already in the makefile)
#endif

//Shared my handle for linux/windows
extern HANDLE my;

//This is needed to convert from floats to longs
#ifndef INPARSER_H
#define INPARSER_H
union inparser {
	long inversion;
	float floatversion;
};
#endif

#define MAXFLOATS 10
#define MAXLINE 120



////////////SERIAL INITIALIZATION//////////////
//Use this if you want to use default ComPortName and BaudRate
void InitSerialPort(void);
//Use this if you want to specify ComPortName and BaudRate
HANDLE SerialInit(char *ComPortName, int BaudRate);

///Get and Receive 1 character
char SerialGetc(HANDLE *hComm);
void SerialPutc(HANDLE *hComm, char txchar);


void Antenna_rx(HANDLE *hComm);
void Short_rx(HANDLE *hComm);
void Open_rx(HANDLE *hComm);
void Load_rx(HANDLE *hComm);
void Antrnna_VNA(HANDLE *hComm);
void Short_VNA(HANDLE *hComm);
void Open_VNA(HANDLE *hComm);
void Load_VNA(HANDLE *hComm);
void Cable_Open_rx(HANDLE *hComm);
void Cable_Short_rx(HANDLE *hComm);
void Noise_rx(HANDLE *hComm);
void Ambient_Hot_rx(HANDLE *hComm);
void Cable_Open_VNA(HANDLE *hComm);
void Cable_Short_VNA(HANDLE *hComm);
void Noise_VNA(HANDLE *hComm);
void Ambient_Hot_VNA(HANDLE *hComm);
void VNA_Rx(HANDLE *hComm);








bool writecsv(char filename[], float field_1, float field_2, float field_3, float field_4, float field_5, float field_6, float field_7);



void Get_temp_sensor_V(HANDLE *hComm,float array[],int num);
void Get_temp_sensor_V(HANDLE *hComm,float array[],int num,int echo);



#endif
