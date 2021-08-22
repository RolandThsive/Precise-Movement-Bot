#define StepX 2
#define DirX 5
#define StepY 3
#define DirY 6
#define EnPin 8

char t;
bool mode = false;
bool runAllowed = false,runAllowed1 = false,runAllowed2 = false;

float calc = 0;
int stepGlobal = 0,i=0;
long autoTurnOff = 0;
long autoTurnOffTime = 30 * 1000; // in seconds

void setup() {
  Serial.begin(9600);
  Serial.println("The program has started");
  pinMode(StepX,OUTPUT);
  pinMode(DirX,OUTPUT);
  pinMode(StepY,OUTPUT);
  pinMode(DirY,OUTPUT);
  pinMode(EnPin,OUTPUT);
  disableStepper();
}

void loop() {
  // put your main code here, to run repeatedly:
  serial();
  if(runAllowed1 || runAllowed2){
    serial();
    enableStepper();
    i++;
    if(i == stepGlobal){
      runAllowed1 = false;
      runAllowed2 = false;
      stepGlobal = 0;
      i = 0;
      disableStepper();
    }
    if(runAllowed1){
      digitalWrite(StepX,HIGH);
      //digitalWrite(StepY,HIGH);
      delayMicroseconds(calc);
      digitalWrite(StepX,LOW); 
      //digitalWrite(StepY,LOW);
      delayMicroseconds(calc);
    }
    else if(runAllowed2){
      digitalWrite(StepY,HIGH);
      //digitalWrite(StepY,HIGH);
      delayMicroseconds(500);
      digitalWrite(StepY,LOW); 
      //digitalWrite(StepY,LOW);
      delayMicroseconds(500);
    }
  }
}


void disableStepper(){
  Serial.println("Released the Motors");
  digitalWrite(EnPin,HIGH);
  autoTurnOff = millis();
  //releaseAndBlock(1,1);
}
void enableStepper(){
    digitalWrite(EnPin,LOW);
}

void joint1(float steps, float speedStep){
  if(steps<0){
   digitalWrite(DirX, HIGH);
 }
 else{
   digitalWrite(DirX, LOW);
 }
 calc = 1/speedStep * 1000000;
 stepGlobal = abs(steps);
 runAllowed1 = true;
}

void joint2(float steps, float speedStep){
  if(steps<0){
   digitalWrite(DirY, HIGH);
 }
 else{
   digitalWrite(DirY, LOW);
 }
 calc = 1/speedStep * 1000000;
 stepGlobal = abs(steps);
 runAllowed2 = true;
}

void serial(){
   if(Serial.available() > 0){
     t = Serial.read();
     if(t == 'm'){
       runAllowed = true;
       
       float steps = Serial.parseFloat();
       float stepSpeed = Serial.parseFloat();
       float joint = Serial.parseFloat();
       Serial.print("Moving to: ");
       Serial.println(steps);
       if(joint == 1){
          joint1(steps,stepSpeed);
        }
       else{
          joint2(steps,stepSpeed);
        }
     }  
     else if(t == 'n'){
       Serial.println("Stopped the Motors");
       runAllowed = false;
       stepGlobal = 0;
       i = 0;
     }
     else if(t == 'b'){
       digitalWrite(EnPin,LOW);
     }
     else if(t == 'd'){
       disableStepper();
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
