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
