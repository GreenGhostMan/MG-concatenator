//#include <SoftwareSerial.h>
//
//SoftwareSerial mySerial(10, 11); // RX, TX
//
//byte reading[10]; // byte array where the Serial readings are stored.
//int result; 
//boolean dataAvailable;
//float O2concentration;
//
//void setup() {
//  Serial.begin(19200);    // Init serial to communicate with sensor.
//  mySerial.begin(9600);   // Init softserial to communicate with other device.
//}
//
//void loop() {
//
//  dataAvailable = false;
//
//  /***  Send message to sensor, which make it send back data.***/
//  
//  byte message[] = { 0x55, 0xAA, 0x7E, 0x02, 0x4F, 0x43, 0x94, 0x0E, 0x0D };
//  Serial.write(message, sizeof(message));
//
//  /***  Read data from sensor into byte array. ***/
//  
//  int MAX_MILLIS_TO_WAIT = 100;
//  unsigned long starttime;
//  starttime = millis();
//  
//  while ( (Serial.available() <11 ) && ((millis() - starttime) < MAX_MILLIS_TO_WAIT) ) {      
//    // not finished jet.
//  }
//  if(Serial.available() < 11) {
//    // not finished jet.
//  }
//  else {
//    for(int n=0; n < 10; n++) {
//      reading[n] = Serial.read(); 
//    }
//
//    dataAvailable = true; 
//  }
//
//  /*** Interpreting the data. ***/
//
//  if (dataAvailable == true) {
//
//    result = reading[7] * 256 + reading[8]; // the readable version.
//
//    result = (int)(reading[7] << 8) | reading[8]; // the bitwise, super efficient version.
//
//    O2concentration = result/10; // measured concentration in %
//  }
//
//  /*** Send the extracted sensor value to other device over softserial. ***/
//  mySerial.println("[" + String(O2concentration) + "]");
//
//  delay(2000);
//}
