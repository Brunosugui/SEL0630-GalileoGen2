/*
 * mSoilMoisture.ino
 * 
 * Soil Moisture module functions
 * 
 * Soil Moisture is a module used for measuring the soil moisture
 * 
 */

/**< function for retrieving Soil Moisture Sensor reading*/
 void mSM_getData(){
  int sm = 0;
  int sm_percent = 0;
  char aux[5];

  sm = analogRead(sm_pin);
  sm_percent = 100 - map(sm, 1023, 0, 0, 100);

  Serial.print("::SM:: Analog Read: ");
  Serial.print(sm);
  Serial.print(" Percent: ");
  Serial.print(sm_percent);
  Serial.println("%");
  sprintf(aux, "%d", sm_percent);
  mMQTT_publish( aux, SOIL_MOISTURE);
  delay(100);
 }
