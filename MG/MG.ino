#include <Wire.h>

int compressor=12;
int fan=11;
int solA=10;
int solB=9;

int pressure_sensor = A0; int pressure_high = 90; int pressure_low = 20;
int purity_sensor = A1;

int delay_millis = 1000;

void Right();
void Left();
void powerOff();
void check_purity();
void check_pressure();
void check_all();

void setup()

{ 
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
  Right();
  delay(delay_millis);
  Left();
  delay(delay_millis);
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
  
}
void check_pressure()
{
  if ( pressure > pressure_high )
  {
    // alarm
    // power off
  }
  else if (pressure < pressure_low)
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
