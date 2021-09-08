
#define StepX 2
#define DirX 5
#define StepY 3
#define DirY 6
#define EnPin 8

char t;
bool mode = false;
bool runAllowed = false;

float calc = 0;
int stepGlobal = 0,i=0;
int wheelRadius = 44.2; //always in mm
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
  serial();
  if(runAllowed){
    serial();
    i++;
    if(i == stepGlobal){
      runAllowed = false;
      stepGlobal = 0;
      i = 0;
      //disableStepper();
    }
    digitalWrite(StepX,HIGH);
    digitalWrite(StepY,HIGH);
    delayMicroseconds(calc);
    digitalWrite(StepX,LOW); 
    digitalWrite(StepY,LOW);
    delayMicroseconds(calc);
  }
  if(((millis() - autoTurnOff) > autoTurnOffTime) && (!runAllowed)){ // auto turn of feature
      disableStepper();
    }
}
