#include <Wire.h>
#include <SoftwareSerial.h> // ? del or not?
//------------------------------------------------
#define MAIN_DELAY      6000
#define BLINK_DELAY     500
#define blink_no        3


//-----------------------------------------------
int compressor=9;   // IN1
int fan=10;         // IN2
int solA=11;        // IN3 // A
int solB=12;        // IN4 // B

int compressor_switch = 5;

void soloA_on() { digitalWrite (solA,LOW); }
void soloA_off()  { digitalWrite (solA,HIGH); }

void soloB_on() { digitalWrite (solB,LOW); }
void soloB_off()  { digitalWrite (solB,HIGH); }
void main_delay_loop(unsigned long now_);

// timer related variables
unsigned long lastMilli = 0;
bool change_status = 0;
bool power_status = 0;
bool test_status =1;

void setup()

{ 
  pinMode (compressor,OUTPUT);
  pinMode (fan,OUTPUT);
  pinMode (solA,OUTPUT);
  pinMode (solB,OUTPUT);
  pinMode (compressor_switch, INPUT);
  
  digitalWrite (compressor, HIGH);  
  digitalWrite (fan, HIGH);        
  soloA_off();
  soloB_off();

  

//  
}

void loop()
{  
  check_power();
  
  unsigned long nowMilli = millis();
  
  if(power_status)
  {
    if(test_status)
    {
      for(int i=0; i<3; i++)
      {
          A_off_B_on(); delay( BLINK_DELAY ); A_on_B_off(); delay( BLINK_DELAY );
      } test_status = 0;
    }
    main_delay_loop(nowMilli);
  }
  else if(!power_status)
  {
    soloA_off();
    soloB_off();
  }
}
