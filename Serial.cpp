#include "Serial.h"
#include <stdio.h>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

HANDLE my;

//Call this for defaults
void InitSerialPort(void)
{
  //Edit this line of code to designate which COM port the arduino board is using!!
  int BaudRate = 115200;
  #ifdef __WIN32__
    char *port = "\\\\.\\COM12";
  #endif
  #if defined __linux__ || __APPLE__
    char *port = "/dev/ttyACM0";
  #endif
  my=SerialInit(port,BaudRate);
}


//Call this for higher level control
HANDLE SerialInit(char *ComPortName, int BaudRate) 
{
  HANDLE hComm;

  #ifdef RPI
  if(wiringPiSetup() == -1) {
      fprintf(stdout, "Unable to start wiringPi: %s\n", strerror (errno));
      return 1;
    }
  hComm = serialOpen(ComPortName,BaudRate);
  if (hComm < 0) {
      fprintf(stderr, "Unable to open serial device: %s\n", strerror (errno));
      return 1;
    }
  return hComm;
  #endif
  
  
  //On linux you need to open the tty port
  #if defined __linux__ || __APPLE__
  printf("Opening Com Port on Linux \n");
  hComm = open(ComPortName,  O_RDWR | O_NOCTTY);
  // Create new termios struc, and call it 'tty' for convention
  struct termios tty;
  memset(&tty, 0, sizeof tty);
  // Read in existing settings, and handle any error
  if(tcgetattr(hComm, &tty) != 0) {
      printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
  }
  tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
  tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
  tty.c_cflag |= CS8; // 8 bits per byte (most common)
  tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
  tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

  tty.c_lflag &= ~ICANON;
  tty.c_lflag &= ~ECHO; // Disable echo
  tty.c_lflag &= ~ECHOE; // Disable erasure
  tty.c_lflag &= ~ECHONL; // Disable new-line echo
  tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
  tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
  tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

  tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
  tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
  // tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)
  // tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT ON LINUX)

  tty.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
  tty.c_cc[VMIN] = 0;

  // Set in/out baud rate to be whatever the baudRate variable is
  cfsetispeed(&tty, BaudRate);
  cfsetospeed(&tty, BaudRate);

  // Save tty settings, also checking for error
  if (tcsetattr(hComm, TCSANOW, &tty) != 0) {
      printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
  }
  #endif

  return hComm;
}
 
 
char SerialGetc(HANDLE *hComm)
{
  char rxchar;

  #ifdef RPI
  if (serialDataAvail(*hComm)) {
      rxchar = serialGetchar(*hComm);
      //fflush(stdout);
    }
  return rxchar;
  #else
  
  
  #if defined __linux__ || __APPLE__
    // Allocate memory for read buffer, set size according to your needs
    memset(&rxchar, '\0', sizeof(rxchar));
    // Read bytes. The behaviour of read() (e.g. does it block?,
    // how long does it block for?) depends on the configuration
    // settings above, specifically VMIN and VTIME
    int num_bytes = read(*hComm, &rxchar, sizeof(rxchar));
    // n is the number of bytes read. n may be 0 if no bytes were received, and can also be -1 to signal an error.
    if (num_bytes <= 0) {
      //printf("Error reading: %s", strerror(errno));
      rxchar = '\0';
    }
    return rxchar;
  #endif

  #endif

}
 
void SerialPutc(HANDLE *hComm, char txchar)
{
  #ifdef RPI
  serialPutchar(*hComm,txchar);
  fflush(stdout);
  return;
  #endif
  
  #if defined __linux__ || __APPLE__
  // Write to serial port
  write(*hComm,&txchar,sizeof(txchar));
  return;
  #endif
}



void Get_temp_sensor_V(HANDLE *hComm,float number_array[],int num) {
  Get_temp_sensor_V(hComm,number_array,num,0);
}

void Get_temp_sensor_V(HANDLE *hComm,float number_array[],int num,int echo) {
  union inparser inputvar;
  std::ofstream myfile;
  SerialPutc(hComm,'w');
  sleep(.1);
  SerialPutc(hComm,'a');
  for (int d = 0;d<num;d++) {
    int i = 0;
    char inLine[MAXLINE];
    char inchar = '\0';
    if (echo) {
      printf("Waiting for characters \n");
    }
    do {
      do {
        inchar = SerialGetc(hComm);
      } while (inchar == '\0');
     if (echo) {
      printf("Receiving: i = %d char = %c chartoint = %d \n",i,inchar,int(inchar));
      }
      inLine[i++] = inchar;

    } while ((inchar != '\r') && (i<MAXLINE));
    if (echo) {
      printf("Response received \n");
    }

    // Format from Arduino:
    // H:nnnnnnnn 
    // voltage(float) is coverted to ASCII at arduino side and transmitted as char
    // Now Convert from ASCII to HEXSTRING to FLOAT
    if (echo) {
      //printf("Converting to Float \n");
    }
    inputvar.inversion = 0;
    for(i=2;i<10;i++){
      if (echo) {
        printf("Hex Digit: i = %d char = %c \n",i,inLine[i]);
      }
      inputvar.inversion <<= 4;
      inputvar.inversion |= (inLine[i] <= '9' ? inLine[i] - '0' : toupper(inLine[i]) - 'A' + 10);
    }
    if (echo) {
      printf("Integer Received = %d \n",inputvar.inversion);
      printf(" \n");
    }
    number_array[d] = inputvar.floatversion;
    printf("Temperature sensor voltage(V) T_%d = %lf \n",(d),number_array[d]);
  }
  //voltage from 7 sensors is saved as .csv file 
  bool write_csv= writecsv("temp_sensor_v.csv",number_array[0],number_array[1],number_array[2],number_array[3],number_array[4],number_array[5],number_array[6]);
  sleep(.3);
}


void Antenna_to_ADC(HANDLE *hComm) {
  char inchar;
  SerialPutc(hComm,'w');
  sleep(.1);
  SerialPutc(hComm,'b');
  //do{
  inchar = SerialGetc(hComm);
  //}while(inchar!='r');
  //printf("inchar received = %d \n", inchar);
  if (inchar=='b'){
  printf("External antenna connected to Digitizer \n");
  }
  return;
}

void Short_to_ADC(HANDLE *hComm) {
  char inchar;
  SerialPutc(hComm,'w');
  sleep(.1);
  SerialPutc(hComm,'c');
  //do{
  inchar = SerialGetc(hComm);
  //}while(inchar!='r');
  //printf("inchar received = %d \n", inchar);
  if (inchar=='c'){
  printf("Short connected to Digitizer \n");
  }
  return;
}

void Open_to_ADC(HANDLE *hComm) {
  char inchar;
  SerialPutc(hComm,'w');
  sleep(.1);
  SerialPutc(hComm,'d');
  //do{
  inchar = SerialGetc(hComm);
  //}while(inchar!='r');
  //printf("inchar received = %d \n", inchar);
  if (inchar=='d'){
  printf("Open connected to Digitizer \n");
  }
  return;
}

void Match_to_ADC(HANDLE *hComm) {
  char inchar;
  SerialPutc(hComm,'w');
  sleep(.1);
  SerialPutc(hComm,'e');
  //do{
  inchar = SerialGetc(hComm);
  //}while(inchar!='r');
  //printf("inchar received = %d \n", inchar);
  if (inchar=='e'){
  printf("Match connected to Digitizer \n");
  }
  return;
}

void Hot_ambient_to_ADC(HANDLE *hComm) {
  char inchar;
  SerialPutc(hComm,'w');
  sleep(.1);
  SerialPutc(hComm,'f');
  //do{
  inchar = SerialGetc(hComm);
  //}while(inchar!='r');
  //printf("inchar received = %d \n", inchar);
  if (inchar=='f'){
  printf("Match connected to Digitizer \n");
  }
  return;
}

void Cable_to_ADC(HANDLE *hComm) {
  char inchar;
  SerialPutc(hComm,'w');
  sleep(.1);
  SerialPutc(hComm,'g');
  //do{
  inchar = SerialGetc(hComm);
  //}while(inchar!='r');
  //printf("inchar received = %d \n", inchar);
  if (inchar=='g'){
  printf("Cable connected to Digitizer \n");
  }
  return;
}

void Noise_to_ADC(HANDLE *hComm) {
  char inchar;
  SerialPutc(hComm,'w');
  sleep(.1);
  SerialPutc(hComm,'h');
  //do{
  inchar = SerialGetc(hComm);
  //}while(inchar!='r');
  //printf("inchar received = %d \n", inchar);
  if (inchar=='h'){
  printf("Noise connected to Digitizer \n");
  }
  return;
}

void VNA_to_ADC(HANDLE *hComm) {
  char inchar;
  SerialPutc(hComm,'w');
  sleep(.1);
  SerialPutc(hComm,'i');
  //do{
  inchar = SerialGetc(hComm);
  //}while(inchar!='r');
  //printf("inchar received = %d \n", inchar);
  if (inchar=='i'){
  printf("VNA connected to Digitizer \n");
  }
  return;
}

void Antenna_to_VNA(HANDLE *hComm) {
  char inchar;
  SerialPutc(hComm,'w');
  sleep(.1);
  SerialPutc(hComm,'j');
  //do{
  inchar = SerialGetc(hComm);
  //}while(inchar!='r');
  //printf("inchar received = %d \n", inchar);
  if (inchar=='j'){
  printf("Antenna connected to VNA \n");
  }
  return;
}

void Short_to_VNA(HANDLE *hComm) {
  char inchar;
  SerialPutc(hComm,'w');
  sleep(.1);
  SerialPutc(hComm,'k');
  //do{
  inchar = SerialGetc(hComm);
  //}while(inchar!='r');
  //printf("inchar received = %d \n", inchar);
  if (inchar=='k'){
  printf("Short connected to VNA \n");
  }
  return;
}

void Open_to_VNA(HANDLE *hComm) {
  char inchar;
  SerialPutc(hComm,'w');
  sleep(.1);
  SerialPutc(hComm,'l');
  //do{
  inchar = SerialGetc(hComm);
  //}while(inchar!='r');
  //printf("inchar received = %d \n", inchar);
  if (inchar=='l'){
  printf("Open connected to VNA \n");
  }
  return;
}

void Match_to_VNA(HANDLE *hComm) {
  char inchar;
  SerialPutc(hComm,'w');
  sleep(.1);
  SerialPutc(hComm,'m');
  //do{
  inchar = SerialGetc(hComm);
  //}while(inchar!='r');
  //printf("inchar received = %d \n", inchar);
  if (inchar=='m'){
  printf("Match connected to VNA \n");
  }
  return;
}

void Hot_Ambient_to_VNA(HANDLE *hComm) {
  char inchar;
  SerialPutc(hComm,'w');
  sleep(.1);
  SerialPutc(hComm,'n');
  //do{
  inchar = SerialGetc(hComm);
  //}while(inchar!='r');
  //printf("inchar received = %d \n", inchar);
  if (inchar=='n'){
  printf("Hot_ambient load connected to VNA \n");
  }
  return;
}

void Cable_to_VNA(HANDLE *hComm) {
  char inchar;
  SerialPutc(hComm,'w');
  sleep(.1);
  SerialPutc(hComm,'o');
  //do{
  inchar = SerialGetc(hComm);
  //}while(inchar!='r');
  //printf("inchar received = %d \n", inchar);
  if (inchar=='o'){
  printf("Cable connected to VNA \n");
  }
  return;
}

void Noise_to_VNA(HANDLE *hComm) {
  char inchar;
  SerialPutc(hComm,'w');
  sleep(.1);
  SerialPutc(hComm,'p');
  //do{
  inchar = SerialGetc(hComm);
  //}while(inchar!='r');
  //printf("inchar received = %d \n", inchar);
  if (inchar=='p'){
  printf("Noise connected to VNA \n");
  }
  return;
}


// write temperature sensor data from arduino to .csv file
bool writecsv(char filename[], float field_1, float field_2, float field_3, float field_4, float field_5, float field_6, float field_7) 
{
std::ofstream file;
file.open(filename, std::ios_base::app);
file<< field_1 << ","<<field_2 << "," <<field_3<<"," <<field_4<<"," <<field_5<<"," <<field_6<<"," <<field_7<< std::endl;
return true;
}  