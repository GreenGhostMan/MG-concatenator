#include <Wire.h>
#include <SoftwareSerial.h>

int compressor=12;
int fan=11;
int solA=10;
int solB=9;

int pressure_sensor = A0; int pressure_high = 90; int pressure_low = 20;
int purity_sensor = A1; int purity_high = 96; int purity_low = 50; // oxygen analyzer

int delay_millis = 1000;

void Right();
void Left();
void powerOff();
void check_purity();
void check_pressure();
void check_all();
void testPrint();

SoftwareSerial mySerial(3,2); // Rx, Tx
SoftwareSerial mySerial2(4,5); // Rx, Tx
void setup()

{ 
  Serial.begin(9600);
  mySerial.begin(9600);
  //mySerial2.begin(9600);
  //while(!Serial){};
  //while(!mySerial){};
  
  pinMode (compressor,OUTPUT);
  pinMode (fan,OUTPUT);
  pinMode (solA,OUTPUT);
  pinMode (solB,OUTPUT);
 
  digitalWrite (compressor,HIGH); 
  digitalWrite (fan,HIGH); 
  digitalWrite (solA,HIGH); 
  digitalWrite (solB,HIGH); 
  
  //attachInterrupt(1,oxygen,FALLING);      // interrupt signal to turn off machine
 
}

void loop()
{  
//  Right();
//  delay(delay_millis);
//  Left();
//  delay(delay_millis);

  testPrint();
  check_all();
}



void Right() 
{
  digitalWrite (solA,HIGH); 
  //digitalWrite (solB,LOW); 
  digitalWrite (solB,HIGH);
}
void Left() 
{
  digitalWrite (solA,LOW); 
  //digitalWrite (solB,HIGH); 
  digitalWrite (solB,LOW);
  
}
void powerOff()
{
   digitalWrite (compressor,LOW); 
   digitalWrite (fan,LOW); 
}

void check_purity() 
{
  purity_sensor = 1*purity_sensor;  // volt to real sensor value
   
    if ( purity_sensor > purity_high )
  {
    // alarm
    // power off
  }
  else if (purity_sensor < purity_low)
  {
    // only alarm
  }
  else 
  {
    // all ok
  } 
}


void check_pressure()
{
  pressure_sensor = 1*pressure_sensor; // volt to real sensor
  if ( pressure_sensor > pressure_high )
  {
    // alarm
    // power off
  }
  else if (pressure_sensor < pressure_low)
  {
    // only alarm
  }
  else 
  {
    // all ok
  }
}



void check_all()
{
  check_purity();
  check_pressure();
}

void testPrint()
{
//  if( mySerial.available() )
//  {
//    Serial.write( mySerial.read() );
//  }

    while (mySerial.available()> 12) {
    char inChar = (char)mySerial.read();
    Serial.write(inChar);
    //mySerial2.print(inChar);
  }
 }
