int incomingByte = 0; // for incoming serial data

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
  Serial.begin(115200); // opens serial port, sets data rate to 115200 bps
  pinMode(LED_BUILTIN,OUTPUT);
  blinktwice(300);
}

void loop() {
  // reply only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    if (incomingByte==49){
      digitalWrite(LED_BUILTIN,HIGH);
      delay(3000);
      digitalWrite(LED_BUILTIN,LOW);
      delay(1000);
      digitalWrite(LED_BUILTIN,HIGH);
      delay(1000);
      digitalWrite(LED_BUILTIN,LOW);
      delay(1000);
      digitalWrite(LED_BUILTIN,HIGH);
      delay(1000);
      digitalWrite(LED_BUILTIN,LOW);
      delay(1000);
      }
    else{
      digitalWrite(LED_BUILTIN,HIGH);
      delay(300);
      digitalWrite(LED_BUILTIN,LOW);
      delay(300);
      }
    // say what you got:
    //Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }
}
