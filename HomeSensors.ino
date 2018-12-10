/*
 * HomeSensors.ino
 * 
 * Main project sketch
 * 
 * Here is basically included libraries used for the project, pins definition,
 * constants definitions and main objects to be used
 * 
 */

 /**< Libraries used*/
#include <Servo.h>
#include <Wire.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <SPI.h>

 /**< Pin definitions*/
#define dht_pin_in    2
#define dht_pin_out   3
#define servo_pin     6
#define buzzer_pin    7
#define sm_pin        A0
#define ldr_pin       A1

/**< Definition of the DHT type to be used*/
#define DHTTYPE DHT11

/**< codes for topic publication */
#define HUMIDITY        0x00
#define TEMPERATURE     0x01
#define SOIL_MOISTURE   0x02
#define LUMINOSITY      0x03
#define SERVO           0x04



Servo servo;
EthernetClient ethClient;
PubSubClient mqttClient(ethClient);

void setup()
{
  board_setup();
}


void loop () {
  board_loop();
  }
