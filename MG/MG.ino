#include <Wire.h>
#include <SoftwareSerial.h>

int compressor=12;
int fan=11;
int solA=10;
int solB=9;

float flow_sensor = 0.0, flow_sensor_high = 90.0, flow_sensor_low = 20.0;
float O2concentration = 0, O2concentration_high = 96.0, O2concentration_low = 50.0; 
int temperature = 0, temp_high = 100, temp_low = 20;

int MAX_MILLIS_TO_WAIT = 100;

void Right();
void Left();
void powerOff();
void check_purity();
void check_pressure();
void check_all();
void readSensor();

byte reading[12]; // byte array where the Serial readings are stored.
boolean dataAvailable;

void setup()

{ 
  pinMode (compressor,OUTPUT);
  pinMode (fan,OUTPUT);
  pinMode (solA,OUTPUT);
  pinMode (solB,OUTPUT);

  //Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  //while(!Serial);  
  while(!Serial1);
  while(!Serial2);
  
  digitalWrite (compressor,HIGH); 
  digitalWrite (fan,HIGH); 
  digitalWrite (solA,HIGH); 
  digitalWrite (solB,HIGH); 
  
  //attachInterrupt(1,oxygen,FALLING);      // interrupt signal to turn off machine
 
}

void loop()
{  
  dataAvailable = false;

  readSensor();
  check_all();
}
