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

//int sensor_tx_pin = 19;
//int sensor_rx_pin = 18;
//int lcd_tx_pin = 19;
//int lcd_rx_pin = 18;

byte reading[12]; // byte array where the Serial readings are stored.
boolean dataAvailable;


void setup()

{ 
  //pinMode (rx_pin,INPUT);
  //pinMode (tx_pin,OUTPUT);
  
  pinMode (compressor,OUTPUT);
  pinMode (fan,OUTPUT);
  pinMode (solA,OUTPUT);
  pinMode (solB,OUTPUT);

  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  while(!Serial);  while(!Serial1);  while(!Serial2);
  
  
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
  //check_all();
}




void readSensor()
{
  byte to_sensor[4] = { 0x11, 0x01, 0x01, 0xED }; //11 01 01 ED
  
  Serial1.write(to_sensor, sizeof(to_sensor));
  unsigned long starttime= millis();
  
  while ( (Serial1.available() <12 ) && ( (millis() - starttime) < MAX_MILLIS_TO_WAIT) );
  if(Serial1.available() < 12) 
  {
    // not finished jet.
  }
  else
  {
    for(int n=0; n < 12; n++) 
    {
      reading[n] = Serial1.read(); 
    }
    dataAvailable = true; 
  }

  /*** Interpreting the data. ***/
  if (dataAvailable == true) {

    //result = reading[7] * 256 + reading[8]; // the readable version.

    int result1 = (int)(reading[3] << 8) | reading[4]; // the bitwise, super efficient version.
    int result2 = (int)(reading[5] << 8) | reading[6];
    int result3 = (int)(reading[7] << 8) | reading[8];
    O2concentration = result1/10.0; // measured concentration in %
    flow_sensor = result2/10.0;
    temperature = result3/10;
    byte to_lcd[12] = { reading[0], reading[1], reading[2], reading[3], reading[4], reading[5], reading[6], reading[7], reading[8], reading[9], reading[10], reading[11] };
    Serial2.write(to_lcd, sizeof(to_lcd));
  }

  /*** Send the extracted sensor value to other device over softserial. ***/
  //Serial.println("O2 status = " + String(O2concentration) + "%");
  //Serial.println("flow = " + String(flow_sensor) + "%");
  //Serial.println("temperature = " + String(temperature) + "C");
  //Serial.println(O2concentration);
  delay(100);

  
}
