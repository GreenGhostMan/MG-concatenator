#include <Wire.h>
#include <SoftwareSerial.h> // delete or not?
//------------------------------------------------
#define MAIN_DELAY      6000
#define BLINK_DELAY     500
#define blink_no        3


//-----------------------------------------------
//============================= hardware ======================================
int compressor=9;   // IN1
int fan=10;         // IN2
int solA=11;        // IN3
int solB=12;        // IN4
int compressor_switch = 5;

void soloA_on()       { digitalWrite (solA,LOW); }
void soloA_off()      { digitalWrite (solA,HIGH); }

void soloB_on()       { digitalWrite (solB,LOW); }
void soloB_off()      { digitalWrite (solB,HIGH); }

//====================== variables for oxy sensor ============================
int flow_rate = 0, flow_5Liter = 50, flow_7Liter = 70, flow_10Liter = 100;
float O2concentration = 0, upperLimit= 96.0, lowerLimit = 50.0; 
int temperature = 0;
int MAX_MILLIS_TO_WAIT = 100;
byte reading[12]; // byte array where the Serial readings are stored.
boolean dataAvailable;

void readSensor();
//============================================================================

// timer related variables
unsigned long lastMilli = 0;
bool change_status = 0;
bool power_status = 0;
bool test_status =1;

void main_delay(unsigned long now_);
void check_sensor();
void check_power(unsigned long now_);

void setup()

{ 
  pinMode (compressor,OUTPUT);
  pinMode (fan,OUTPUT);
  pinMode (solA,OUTPUT);
  pinMode (solB,OUTPUT);
  pinMode (compressor_switch, INPUT);
  
  //Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  //while(!Serial);  
  while(!Serial1);
  while(!Serial2);
  
  digitalWrite (compressor, HIGH);  
  digitalWrite (fan, HIGH);        
  soloA_off();
  soloB_off();
}

void loop()
{  
  unsigned long nowMilli = millis();
  dataAvailable = false;     // helper variable for readSensor() function
  
  check_switch();

  check_power(nowMilli); 
  
  readSensor();              // read from purity sensor every ~ >100ms and send to lcd

  check_sensor();            // to add some features


}



void check_power(unsigned long now_)
{
  if(power_status)
  {
    main_delay(now_);
  }
  
  else if(!power_status)
  {
    soloA_off();
    soloB_off();
  }
}
