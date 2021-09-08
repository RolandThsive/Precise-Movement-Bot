#include "MotorDriver.h"
int k = 1;
int data = 100;
MotorDriver motor;
char c = 'k';
void setup(){
    // initialize
  motor.begin();
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), brakes, RISING); //emergency brake
}
 
void loop(){
   // to implement the serial input here
  if(k == 1){
    movement(data,data,1000);
    delay(1000);
  }
  else{
    
  }
}

void movement(int speedv1,int speedv2, int timev){
  int realSpeed1 = map(speedv1,0,255,0,100); // correct speed to be determined
  int realSpeed2= map(speedv2,0,255,0,100);  // correct speed to be determined
  motor.speed(0,speedv1);
  motor.speed(1,speedv2);
  delay(timev);
  motor.brake(0);
  motor.brake(1);
}
void brakes(){
  k = k*-1;
  motor.brake(0);
  motor.brake(1);
}
void serialEvent(){
  while(Serial.available()){
    int k = Serial.parseInt();
    if(k != 0){
      data = k;
      Serial.println(data);
    }
  }
}
