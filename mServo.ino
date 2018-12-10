/*
 * mServo.ino
 * 
 * Servo module functions
 * 
 * Servo motor functions, 
 * 
 * Servo module used:  Tower Pro Micro Servo 9g
 * 
 */

/**< Servo module initialization*/
 void mServo_init(){
  servo.attach(servo_pin);
  servo.write(0);
 }

/**< Servo rotate function*/
void mServo_write(int rotate){
  servo.write(rotate);
}

/**< Servo activation function*/
void mServo_activate(int interval){
  mServo_write(179);
  delay(interval);
  mServo_write(0);
}
