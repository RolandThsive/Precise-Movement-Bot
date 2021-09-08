#include <AccelStepper.h>
#include <MultiStepper.h>

#define DIR1 8
#define PUL1 9
#define ENA1 7


#define DIR2 4
#define PUL2 3
#define ENA2 5

char t;
bool mode = false;

int wheelRadius = 300; //always in mm
float steps, stepSpeed;

AccelStepper s1(1,PUL1,DIR1);
AccelStepper s2(2,PUL2,DIR2);

MultiStepper steppers;
void setup() {
  Serial.begin(9600);
  Serial.println("This B starts!");
  pinMode(ENA1,OUTPUT);
  pinMode(ENA2,OUTPUT);

  steppers.addStepper(s1);
  steppers.addStepper(s2);
  
  s1.setMaxSpeed(2000);
  s2.setMaxSpeed(2000);

  s1.disableOutputs();
  s2.disableOutputs();
  digitalWrite(ENA1,HIGH);
  digitalWrite(ENA2,HIGH);
}

void loop() {
  serial();
  delay(50);
}

void serial(){
  if(Serial.available() > 0){
     t = Serial.read();
     if(t == 'm'){
       s1.enableOutputs();
       s2.enableOutputs();
       releaseAndBlock(0,0);
       
       steps = Serial.parseFloat();
       stepSpeed = Serial.parseFloat();
       
       if(mode){
        steps = (steps/(wheelRadius*2*3.14)) * 800;
       }
       Serial.print("Steps/mm moved: ");
       Serial.println(abs(steps - s1.currentPosition()));
       movement(stepSpeed,stepSpeed,steps,steps);
       //reset();
       getInfo();
     }
     else if(t == 'r'){
       
     }
     else if(t == 'n'){
       stopStepper();
     }
     else if(t == 's'){
        reset();
        getInfo();
     }
     else if(t == 'p'){
        getInfo(); 
     }
     else if(t == 'b'){
       releaseAndBlock(0,0);
       Serial.println("Motors were Blocked");
     }
     else if(t == 'c'){
      mode = !mode;
      if(mode)
        Serial.println("Mode was changed to mm");
      else
        Serial.println("Mode was changed to steps");
    }
  }
}

void reset(){
  s1.setCurrentPosition(0);
  s2.setCurrentPosition(0);
  Serial.println("Positions Were Reset");
}
void stopStepper(){
  Serial.println("Stopped and Released the Motors"); //print action
       
  s1.stop();
  s1.disableOutputs();   
       
  s2.stop();
  s2.disableOutputs();
  releaseAndBlock(1,1);
}
void releaseAndBlock(int a, int b){
  digitalWrite(ENA1,a);
  digitalWrite(ENA2,b);
}
void getInfo(){
  Serial.print( "Stepper 1: ");
  Serial.println(s1.currentPosition());

  Serial.print("Stepper 2: ");
  Serial.println(s2.currentPosition());
}
void movement(int ss1, int ss2, float steps1,float steps2){
  long positions[2];
  
  positions[0] = steps1;
  positions[1] = steps1;
  
  s1.setMaxSpeed(ss1);
  s2.setMaxSpeed(ss2);
  steppers.moveTo(positions);
  steppers.runSpeedToPosition();
}
