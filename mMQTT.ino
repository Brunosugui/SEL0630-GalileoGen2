/*
 * mMQTT.ino
 * 
 * MQTT module functions
 * 
 * MQTT is a web protocol for communication, this protocol consists in publish data on topics on a broker server
 * and read data from topics (subscribe)
 * 
 */

/**< General Definitions for MQTT connection*/
#define mqtt_server  "broker.hivemq.com"
#define mqtt_port 1883
#define MQTT_USER "Buddha"
#define MQTT_PASSWORD "Buddha"

/**< MQTT Topics to publish or subscribe*/
#define MQTT_PUBLISH          "SEL0630/GALILEO/CONNECTED"
#define MQTT_PUBLISH_CH_0     "SEL0630/GALILEO/HUMIDITY"
#define MQTT_PUBLISH_CH_1     "SEL0630/GALILEO/TEMPERATURE"
#define MQTT_PUBLISH_CH_2     "SEL0630/GALILEO/SOIL_MOISTURE"
#define MQTT_PUBLISH_CH_3     "SEL0630/GALILEO/LUMINOSITY"
#define MQTT_SUBSCRIBE_CH_0   "SEL0630/ANDROID/SERVO"

/**< Keyword for activating Servo*/
#define SERVO_ACTIVATE        "ON"

/**< Callback function for handling new incoming messages to subscribed topic*/
void mMQTT_callback(char* topic, byte *payload, unsigned int length){
    Serial.println("::MQTT:: -------new message from broker-----");
    Serial.print("::MQTT:: channel:");
    Serial.println(topic);
    Serial.print("::MQTT:: data:");
    Serial.write(payload, length);
    Serial.println();
    mMQTT_parseCallback(topic, payload, length);
    memset(payload, 0, length);
}

/**< function for 'understanding' callback message*/
void mMQTT_parseCallback(char* topic, byte *payload, unsigned int length){
  if(!strcmp(topic, MQTT_SUBSCRIBE_CH_0)){
    if(!strncmp((char*)payload, SERVO_ACTIVATE, length)){
      mServo_activate(1000);
    }
  }
}

/**< MQTT initialization function*/
 void mMQTT_init(){
  mqttClient.setServer(mqtt_server, mqtt_port);
  mqttClient.setCallback(mMQTT_callback);
  if(mqttClient.connect("HomeSensor")){
    Serial.print("::MQTT:: MQTT connected to broker: ");
    Serial.print(mqtt_server);
    Serial.print(" at port ");
    Serial.println(mqtt_port); 
    if(mqttClient.publish(MQTT_PUBLISH, "connected!")){
        Serial.println("::MQTT:: Successfully published!");
      }else{
        Serial.println("::MQTT:: Failed to publish.");
      }
      if(mqttClient.subscribe(MQTT_SUBSCRIBE_CH_0)){
        Serial.println("::MQTT:: Successfully subscribed!");
      }else{
        Serial.println("::MQTT:: Failed to subscribe");
      }
  }else{
    Serial.print("::MQTT:: Failed to connect to MQTT broker");
  }
 }

/**< function for checking MQTT connection to broker*/
 boolean mMQTT_checkConnection(){
  if(!mqttClient.connected()){
      return mMQTT_reconnect();
  }else{
    return true;
  }
 }

 /**< function for reconnecting MQTT to broker*/
boolean mMQTT_reconnect(){
  while(!mqttClient.connected()){
    mqttClient.disconnect();
    Serial.println("::MQTT:: Attempting MQTT connection...");
    String clientId = "HomeSensor-";
    clientId += String(random(0xffff), HEX);
    if(mqttClient.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD)){
      Serial.println("::MQTT:: Connected!");
      if(mqttClient.publish(MQTT_PUBLISH, "reconnected!")){
        Serial.println("::MQTT:: Successfully published!");
      }else{
        Serial.println("::MQTT:: Failed to publish.");
      }
      if(mqttClient.subscribe(MQTT_SUBSCRIBE_CH_0)){
        Serial.println("::MQTT:: Successfully subscribed!");
      }else{
        Serial.println("::MQTT:: Failed to subscribe");
      }
      delay(100);
      return true;
    }
    else{
      Serial.print("::MQTT:: Failed to reconnect, error = ");
      Serial.print(mqttClient.state());
      Serial.println(" trying again in 5 seconds...");
      board_ethernetCheck();
      delay(5000);
    }
  }
  return false;
}

/**< function for publishing messages to specific topic*/
boolean mMQTT_publish(char* Data, int topic){
    switch(topic){
      case HUMIDITY:
        return mqttClient.publish(MQTT_PUBLISH_CH_0, Data);
        break;
        case TEMPERATURE:
        return mqttClient.publish(MQTT_PUBLISH_CH_1, Data);
        break;
        case SOIL_MOISTURE:   
        return mqttClient.publish(MQTT_PUBLISH_CH_2, Data);
        break;
        case LUMINOSITY:
        return mqttClient.publish(MQTT_PUBLISH_CH_3, Data);
        break;
        
    }
}

  
