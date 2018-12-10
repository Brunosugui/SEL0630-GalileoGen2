/*
 * mDHT.ino
 * 
 * DHT module functions
 * 
 * DHT is a Humidity and Temperature module
 * 
 * There is a problem regarding to DHT library for Intel Galileo, see Project Report for more info
 * 
 */

/**< Function for retrieving DHT sensor reading*/
 void mDHT_getData(){
  DHT_4_Galileo dht(dht_pin_out, dht_pin_in);
  int response = dht.read();
  char aux[5];

  if(response == DHT_4_Galileo::DHT_READ_SUCCESS){
    Serial.println("RESULTS:");
    Serial.println("-----------------");
    Serial.print("Humidity:");
    Serial.print(dht.humidity,1);
    sprintf(aux, "%d", dht.humidity);
    mMQTT_publish(aux, HUMIDITY);
    memset(aux, 0, 5);
    Serial.print(",\t");
    Serial.print("Temperature (C):");
    Serial.println(dht.temperature,1);
    sprintf(aux, "%d", dht.temperature);
    mMQTT_publish(aux, TEMPERATURE);
  }else{
    Serial.print("::DHT:: DHT error: ");
    Serial.println(response);
  }
  
 }
