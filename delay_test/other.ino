void A_off_B_on()
{
  soloA_off();
  soloB_on();
  change_status = 1;
}

void A_on_B_off()
{
  soloA_on();
  soloB_off();
  change_status = 0;
}

void check_power()
{
  if(digitalRead(compressor_switch))   // working
  {
    digitalWrite (compressor, 0);  
    digitalWrite (fan, 0);  
    power_status = 1;
  }
  else if( !(digitalRead(compressor_switch)) ){  // not working
    digitalWrite (compressor, 1);  
    digitalWrite (fan, 1);  
    power_status = 0;
  }
  
}

void main_delay_loop(unsigned long now_)
{
   if (now_ - lastMilli >= MAIN_DELAY) //-------------------------
  {
    if( change_status == 1 )
    {
      A_on_B_off();
    }
    else {
      A_off_B_on();
    }
    lastMilli = now_;
  }          
}
