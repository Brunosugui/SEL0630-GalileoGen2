/**
 * galileo_board.ino
 * 
 * here are placed board related codes, like basic IOs signals, board initialization, etc...
 * 
 */
 
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; 
byte ip[] = {192, 168, 0, 10};


/**< Physical initialization */
void board_init(){
  bool state = HIGH;
  for(int i = 0; i < 8; i++){
    digitalWrite(buzzer_pin, state);   
    state = !state;
    delay(50);                       
  }
}

/**< Pins initialization*/
void board_pins_init(){
  pinMode(buzzer_pin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

/**< sensor modules initialization*/
void board_sensors_init(){
  mServo_init();
}

/**< Function for checking internet connection over Ethernet cable*/
void board_ethernetCheck(){
    if(Ethernet.begin(mac) == 0){
      Serial.println("::Ethernet:: Failed to configure Ethernet using DHCP");
      Serial.println("::Ethernet:: Attempting to configure Ethernet using Static IP");
      Ethernet.begin(mac, ip);
      Serial.println("::Ethernet:: Checking ifconfig");
    }else{
      Serial.println("::Ethernet:: Connected!");
      system("ifup eth0");
      mMQTT_init();
    }
}

/**< Board General initialization*/
void board_setup(){
  Serial.begin(115200);
  board_pins_init();
  board_ethernetCheck();
  delay(1500);
  board_sensors_init();
  board_init();
}

/**< Board Loop*/
void board_loop(){
  if(mMQTT_checkConnection()){
    mDHT_getData();
    delay(100);
    mSM_getData();
    delay(100);
    mLDR_getData();
    delay(100);
    mqttClient.loop();
  }else{
    Serial.println("::MQTT:: MQTT not connected");
  }
}
