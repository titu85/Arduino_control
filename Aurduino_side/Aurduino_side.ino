//#include <Arduino.h>
//
//int incomingByte = 0; // for incoming serial data
//
//void blinktwice(int d) {
// digitalWrite(LED_BUILTIN,HIGH);
// delay(d);
// digitalWrite(LED_BUILTIN,LOW);
// delay(d);
// digitalWrite(LED_BUILTIN,HIGH);
// delay(d);
// digitalWrite(LED_BUILTIN,LOW);
// delay(d);
//}

//void setup() {
// Serial.begin(115200); // opens serial port, sets data rate to 115200 bps
// pinMode(LED_BUILTIN,OUTPUT);
// //blinktwice(300);
//}

//void loop() {
// // reply only when you receive data:
// if (Serial.available() > 0) {
// // read the incoming byte:
// incomingByte = Serial.read();
// if (incomingByte==49){
// digitalWrite(LED_BUILTIN,HIGH);
// delay(3000);
// digitalWrite(LED_BUILTIN,LOW);
// delay(1000);
// digitalWrite(LED_BUILTIN,HIGH);
// delay(1000);
// digitalWrite(LED_BUILTIN,LOW);
// delay(1000);
// digitalWrite(LED_BUILTIN,HIGH);
// delay(1000);
// digitalWrite(LED_BUILTIN,LOW);
// delay(1000);
// }
// else{
// digitalWrite(LED_BUILTIN,HIGH);
// delay(300);
// digitalWrite(LED_BUILTIN,LOW);
// delay(300);
// }
// // say what you got:
// //Serial.print("I received: ");
// Serial.println(incomingByte, DEC);
//
// }
//}

//----------------------------------------------
//----------------------------------------------
//#include <Arduino.h>
union inparser {
long inversion;
float floatversion;
} ;

int T1 = A1;
int T2 = A2;
int T3 = A3;
int T4 = A4;
int T5 = A5;
int T6 = A6;
int T7 = A7; // potentiometer wiper (middle terminal) connected to analog pin 3 // outside leads to ground and +5V
float val = 0;

int tempt_1=0;
int tempt_2=0;
int tempt_3=0;
int tempt_4=0;
int tempt_5=0;
int tempt_6=0;
int tempt_7=0;

int tempt_11=0;
int tempt_21=0;
int tempt_31=0;
int tempt_41=0;
int tempt_51=0;
int tempt_61=0;
int tempt_71=0;

int tempt_12=0;
int tempt_22=0;
int tempt_32=0;
int tempt_42=0;
int tempt_52=0;
int tempt_62=0;
int tempt_72=0;

int tempt_13=0;
int tempt_23=0;
int tempt_33=0;
int tempt_43=0;
int tempt_53=0;
int tempt_63=0;
int tempt_73=0;

extern void SendReceiveNumber(void);

void blinktwice(int d) {
digitalWrite(LED_BUILTIN,HIGH);
delay(d);
digitalWrite(LED_BUILTIN,LOW);
delay(d);
digitalWrite(LED_BUILTIN,HIGH);
delay(d);
digitalWrite(LED_BUILTIN,LOW);
delay(d);
}

void setup() {
// put your setup code here, to run once:
Serial.begin(115200);
//Turn on the Builtin LED
pinMode(LED_BUILTIN,OUTPUT);
pinMode(27,OUTPUT);
pinMode(29,OUTPUT);
pinMode(31,OUTPUT);
pinMode(33,OUTPUT);
pinMode(35,OUTPUT);
pinMode(37,OUTPUT);
pinMode(39,OUTPUT);
pinMode(41,OUTPUT);
pinMode(43,OUTPUT);
pinMode(45,OUTPUT);

//Blink once to notify that the arduino is ready
//blinktwice(1000);
blinktwice(100);
}

void loop() { 
char c;
char command;

//Ok so this code here basically waits until the arduino
//read a 'w'. 
//do {
// c=Serial.read();
//} while (c != 'w');
//In order to notify the user that the arduino received a w
//and a new line below.
//digitalWrite(LED_BUILTIN,HIGH);
union inparser inputvar;
//Serial.print('q');
//Set the first Neopixel to red
//CircuitPlayground.setPixelColor(0,255,0,0);
do {
c=Serial.read();
} while (c != 'w');
do {
command=Serial.read();
//blinktwice(1000);
} while ((command != 'T') && (command != 'a') && (command != 'b') && (command != 'c') && (command != 'd') && (command != 'e') && (command != 'f') && (command != 'g') && (command != 'h') && (command != 'i') && (command != 'j') && (command != 'k') && (command != 'l') && (command != 'm') && (command != 'n') && (command != 'o') && (command != 'p')&&(command != 'q')&& (command != 'r'));

if (command=='b'){
//Ant_rx U1Rf1-U5Rf1
digitalWrite(27, LOW); //U1A
digitalWrite(29, LOW); //U1B
digitalWrite(31, LOW); //U2A
digitalWrite(33, LOW); //U2B
digitalWrite(35, LOW); //U3A
digitalWrite(37, LOW); //U3C
digitalWrite(39, HIGH); //U4A
digitalWrite(41, LOW); //U4B
digitalWrite(43, HIGH); //U5A
digitalWrite(45, LOW);//U5B
digitalWrite(47, LOW);//U6A
digitalWrite(49, LOW);//U6B
Serial.print('b');
}

if (command=='c'){
//Short_rx U1Rf2-U5Rf1
digitalWrite(27, HIGH); //U1A
digitalWrite(29, LOW); //U1B
digitalWrite(31, LOW); //U2A
digitalWrite(33, LOW); //U2B
digitalWrite(35, LOW); //U3A
digitalWrite(37, LOW); //U3C
digitalWrite(39, HIGH); //U4A
digitalWrite(41, LOW); //U4B
digitalWrite(43, HIGH); //U5A
digitalWrite(45, LOW);//U5B
digitalWrite(47, LOW);//U6A
digitalWrite(49, LOW);//U6B
Serial.print('c');
}
if (command=='d'){
//Open_Rx U1Rf3-U5Rf1
digitalWrite(27, LOW); //U1A
digitalWrite(29, HIGH); //U1B
digitalWrite(31, LOW); //U2A
digitalWrite(33, LOW); //U2B
digitalWrite(35, LOW); //U3A
digitalWrite(37, LOW); //U3C
digitalWrite(39, HIGH); //U4A
digitalWrite(41, LOW); //U4B
digitalWrite(43, HIGH); //U5A
digitalWrite(45, LOW);//U5B
digitalWrite(47, LOW);//U6A
digitalWrite(49, LOW);//U6B
Serial.print('d');
}
if (command=='e'){
//Load_Rx U1Rf4-U5Rf1
digitalWrite(27, HIGH); //U1A
digitalWrite(29, HIGH); //U1B
digitalWrite(31, LOW); //U2A
digitalWrite(33, LOW); //U2B
digitalWrite(35, LOW); //U3A
digitalWrite(37, LOW); //U3C
digitalWrite(39, HIGH); //U4A
digitalWrite(41, LOW); //U4B
digitalWrite(43, HIGH); //U5A
digitalWrite(45, LOW);//U5B
digitalWrite(47, LOW);//U6A
digitalWrite(49, LOW);//U6B
Serial.print('e');
}
if (command=='f'){
//Ant_VNA U1Rf1-U3Rfc
digitalWrite(27, LOW); //U1A
digitalWrite(29, LOW); //U1B
digitalWrite(31, LOW); //U2A
digitalWrite(33, LOW); //U2B
digitalWrite(35, LOW); //U3A
digitalWrite(37, HIGH); //U3C
digitalWrite(39, HIGH); //U4A
digitalWrite(41, LOW); //U4B
digitalWrite(43, LOW); //U5A
digitalWrite(45, HIGH);//U5B
digitalWrite(47, LOW);//U6A
digitalWrite(49, LOW);//U6B
Serial.print('f');
}

if (command=='g'){
//Short_VNA U1Rf2-U3Rfc
digitalWrite(27, HIGH); //U1A
digitalWrite(29, LOW); //U1B
digitalWrite(31, LOW); //U2A
digitalWrite(33, LOW); //U2B
digitalWrite(35, LOW); //U3A
digitalWrite(37, HIGH); //U3C
digitalWrite(39, HIGH); //U4A
digitalWrite(41, LOW); //U4B
digitalWrite(43, LOW); //U5A
digitalWrite(45, HIGH);//U5B
digitalWrite(47, LOW);//U6A
digitalWrite(49, LOW);//U6B
Serial.print('g');
}
if (command=='h'){
//Open_VNA  U1Rf3-U3Rfc
digitalWrite(27, LOW); //U1A
digitalWrite(29, HIGH); //U1B
digitalWrite(31, LOW); //U2A
digitalWrite(33, LOW); //U2B
digitalWrite(35, LOW); //U3A
digitalWrite(37, HIGH); //U3C
digitalWrite(39, HIGH); //U4A
digitalWrite(41, LOW); //U4B
digitalWrite(43, LOW); //U5A
digitalWrite(45, HIGH);//U5B
digitalWrite(47, LOW);//U6A
digitalWrite(49, LOW);//U6B
Serial.print('h');
}

if (command=='i'){
//Load_VNA  U1Rf4-U3Rfc
digitalWrite(27, HIGH); //U1A
digitalWrite(29, HIGH); //U1B
digitalWrite(31, LOW); //U2A
digitalWrite(33, LOW); //U2B
digitalWrite(35, LOW); //U3A
digitalWrite(37, HIGH); //U3C
digitalWrite(39, HIGH); //U4A
digitalWrite(41, LOW); //U4B
digitalWrite(43, LOW); //U5A
digitalWrite(45, HIGH);//U5B
digitalWrite(47, LOW);//U6A
digitalWrite(49, LOW);//U6B
Serial.print('i');
}

if (command=='j'){
//Cable_Open_Rx U2Rf1-U5Rf1
digitalWrite(27, LOW); //U1A
digitalWrite(29, LOW); //U1B
digitalWrite(31, LOW); //U2A
digitalWrite(33, LOW); //U2B
digitalWrite(35, LOW); //U3A
digitalWrite(37, LOW); //U3C
digitalWrite(39, LOW); //U4A
digitalWrite(41, HIGH); //U4B
digitalWrite(43, HIGH); //U5A
digitalWrite(45, LOW);//U5B
digitalWrite(47, HIGH);//U6A
digitalWrite(49, LOW);//U6B
Serial.print('j');
}

if (command=='k'){
//Cable_short_Rx U2Rf1-U5Rf1
digitalWrite(27, LOW); //U1A
digitalWrite(29, LOW); //U1B
digitalWrite(31, LOW); //U2A
digitalWrite(33, LOW); //U2B
digitalWrite(35, LOW); //U3A
digitalWrite(37, LOW); //U3C
digitalWrite(39, LOW); //U4A
digitalWrite(41, HIGH); //U4B
digitalWrite(43, HIGH); //U5A
digitalWrite(45, LOW);//U5B
digitalWrite(47, LOW);//U6A
digitalWrite(49, HIGH);//U6B
Serial.print('k');
}

if (command=='l'){
//Noise_Rx U2Rf2-U5Rf1
digitalWrite(27, LOW); //U1A
digitalWrite(29, LOW); //U1B
digitalWrite(31, HIGH); //U2A
digitalWrite(33, LOW); //U2B
digitalWrite(35, LOW); //U3A
digitalWrite(37, LOW); //U3C
digitalWrite(39, LOW); //U4A
digitalWrite(41, HIGH); //U4B
digitalWrite(43, HIGH); //U5A
digitalWrite(45, LOW);//U5B
digitalWrite(47, LOW);//U6A
digitalWrite(49, LOW);//U6B
Serial.print('l');
}

if (command=='m'){
//Ambient_Hot_Rx U2Rf3-U5Rf1
digitalWrite(27, LOW); //U1A
digitalWrite(29, LOW); //U1B
digitalWrite(31, LOW); //U2A
digitalWrite(33, HIGH); //U2B
digitalWrite(35, LOW); //U3A
digitalWrite(37, LOW); //U3C
digitalWrite(39, LOW); //U4A
digitalWrite(41, HIGH); //U4B
digitalWrite(43, HIGH); //U5A
digitalWrite(45, LOW);//U5B
digitalWrite(47, LOW);//U6A
digitalWrite(49, LOW);//U6B
Serial.print('m');
}
if (command=='n'){
//Cable_Open_VNA U2Rf1-U3Rfc
digitalWrite(27, LOW); //U1A
digitalWrite(29, LOW); //U1B
digitalWrite(31, LOW); //U2A
digitalWrite(33, LOW); //U2B
digitalWrite(35, LOW); //U3A
digitalWrite(37, HIGH); //U3C
digitalWrite(39, LOW); //U4A
digitalWrite(41, HIGH); //U4B
digitalWrite(43, LOW); //U5A
digitalWrite(45, HIGH);//U5B
digitalWrite(47, HIGH);//U6A
digitalWrite(49, LOW);//U6B
Serial.print('n');
}

if (command=='o'){
//Cable_short_VNA U2Rf1-U3Rfc
digitalWrite(27, LOW); //U1A
digitalWrite(29, LOW); //U1B
digitalWrite(31, LOW); //U2A
digitalWrite(33, LOW); //U2B
digitalWrite(35, LOW); //U3A
digitalWrite(37, HIGH); //U3C
digitalWrite(39, LOW); //U4A
digitalWrite(41, HIGH); //U4B
digitalWrite(43, LOW); //U5A
digitalWrite(45, LOW);//U5B
digitalWrite(47, LOW);//U6A
digitalWrite(49, HIGH);//U6B
Serial.print('o');
}

if (command=='p'){
//Noise_VNA U2Rf2-U3Rfc
digitalWrite(27, LOW); //U1A
digitalWrite(29, LOW); //U1B
digitalWrite(31, HIGH); //U2A
digitalWrite(33, LOW); //U2B
digitalWrite(35, LOW); //U3A
digitalWrite(37, HIGH); //U3C
digitalWrite(39, LOW); //U4A
digitalWrite(41, HIGH); //U4B
digitalWrite(43, LOW); //U5A
digitalWrite(45, HIGH);//U5B
digitalWrite(47, LOW);//U6A
digitalWrite(49, LOW);//U6B
Serial.print('p');
}

if (command=='q'){
//Ambient_Hot_VNA U2Rf3-U3Rfc
digitalWrite(27, LOW); //U1A
digitalWrite(29, LOW); //U1B
digitalWrite(31, LOW); //U2A
digitalWrite(33, HIGH); //U2B
digitalWrite(35, LOW); //U3A
digitalWrite(37, HIGH); //U3C
digitalWrite(39, LOW); //U4A
digitalWrite(41, HIGH); //U4B
digitalWrite(43, LOW); //U5A
digitalWrite(45, HIGH);//U5B
digitalWrite(47, LOW);//U6A
digitalWrite(49, LOW);//U6B
Serial.print('q');
}

if (command=='r'){
//VNA_Rx U5Rf1-U3Rfc
digitalWrite(27, LOW); //U1A
digitalWrite(29, LOW); //U1B
digitalWrite(31, HIGH); //U2A
digitalWrite(33, HIGH); //U2B
digitalWrite(35, HIGH); //U3A
digitalWrite(37, LOW); //U3C
digitalWrite(39, LOW); //U4A
digitalWrite(41, HIGH); //U4B
digitalWrite(43, HIGH); //U5A
digitalWrite(45, LOW);//U5B
digitalWrite(47, LOW);//U6A
digitalWrite(49, LOW);//U6B
Serial.print('r');
}


if (command=='a'){
//blinktwice(1000);
analogReadResolution(12);
tempt_11 = analogRead(T1);
tempt_21 = analogRead(T2);
tempt_31 = analogRead(T3);
tempt_41 = analogRead(T4);
tempt_51 = analogRead(T5);
tempt_61 = analogRead(T6);
tempt_71 = analogRead(T7);

tempt_12 = analogRead(T1);
tempt_22 = analogRead(T2);
tempt_32 = analogRead(T3);
tempt_42 = analogRead(T4);
tempt_52 = analogRead(T5);
tempt_62 = analogRead(T6);
tempt_72 = analogRead(T7);

tempt_13 = analogRead(T1);
tempt_23 = analogRead(T2);
tempt_33 = analogRead(T3);
tempt_43 = analogRead(T4);
tempt_53 = analogRead(T5);
tempt_63 = analogRead(T6);
tempt_73 = analogRead(T7);

tempt_1= (tempt_11 + tempt_12 + tempt_13)/3;
tempt_2= (tempt_21 + tempt_22 + tempt_23)/3;
tempt_3= (tempt_31 + tempt_32 + tempt_33)/3;
tempt_4= (tempt_41 + tempt_42 + tempt_43)/3;
tempt_5= (tempt_51 + tempt_52 + tempt_53)/3;
tempt_6= (tempt_61 + tempt_62 + tempt_63)/3;
tempt_7= (tempt_71 + tempt_72 + tempt_73)/3;

val =(tempt_11*3.3)/4096;
float Volt_1=val;
inputvar.floatversion = Volt_1;
char outline[20];
sprintf(outline, "H:%08lx \0",inputvar.inversion);
Serial.print(outline);
Serial.print('\r');

val =(tempt_21*3.3)/4096;
float Volt_2=val;
inputvar.floatversion = Volt_2;
sprintf(outline, "H:%08lx \0",inputvar.inversion);
Serial.print(outline);
Serial.print('\r');
val =(tempt_31*3.3)/4096;
float Volt_3=val;
inputvar.floatversion = Volt_3;
sprintf(outline, "H:%08lx \0",inputvar.inversion);
Serial.print(outline);
Serial.print('\r');
val =(tempt_41*3.3)/4096;
float Volt_4=val;
inputvar.floatversion = Volt_4;
sprintf(outline, "H:%08lx \0",inputvar.inversion);
Serial.print(outline);
Serial.print('\r');
val =(tempt_51*3.3)/4096;
float Volt_5=val;
inputvar.floatversion = Volt_5;
sprintf(outline, "H:%08lx \0",inputvar.inversion);
Serial.print(outline);
Serial.print('\r');

val =(tempt_6*3.3)/4096;
float Volt_6=val;
inputvar.floatversion = Volt_6;
sprintf(outline, "H:%08lx \0",inputvar.inversion);
Serial.print(outline);
Serial.print('\r');

val =(tempt_7*3.3)/4096;
float Volt_7=val;
inputvar.floatversion = Volt_7;
sprintf(outline, "H:%08lx \0",inputvar.inversion);
Serial.print(outline);
Serial.print('\r');
}
//if (Serial.available() > 0) {
//command=Serial.read();
//blinktwice(1000);

//}
//After that it will run the DoHIL routine
//SendReceiveNumber();

}
