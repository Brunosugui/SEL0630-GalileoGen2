/*
 * mLDR.ino
 * 
 * LDR module functions
 * 
 * LDR stands for Light Dependant Resistor
 * 
 */

/**< Function for retrieving LDR sensor reading*/
 void mLDR_getData(){
  char aux[5];
  int ldr_read = analogRead(ldr_pin);
  int ldr_percent = 100 - map(ldr_read, 1024, 0, 0, 100);
  Serial.print("::LDR:: Analog Read: ");
  Serial.print(ldr_read);
  Serial.print(" Percent: ");
  Serial.print(ldr_percent);
  Serial.println("%");
  sprintf(aux, "%d", ldr_percent);
  mMQTT_publish(aux, LUMINOSITY);
  mLDR_activate(ldr_percent);
 }

void mLDR_activate(int ldr_percent){
  if(ldr_percent < 55){
    digitalWrite(LED_BUILTIN, HIGH);
  }else{
    digitalWrite(LED_BUILTIN, LOW);
  }
}
