
void main_delay(unsigned long now_)
{
  // testing purpose ---------------------------------------------------------------------for test run check
  if(test_status)
    {
      for(int i=0; i<3; i++)
      {
          A_off_B_on(); delay( BLINK_DELAY ); A_on_B_off(); delay( BLINK_DELAY );
      } test_status = 0;
    }
  //-------------------------------------------------------------------------------------------------------
   if (now_ - lastMilli >= MAIN_DELAY) 
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
