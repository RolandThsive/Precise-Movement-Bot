 #include <AccelStepper.h>

#define DIR1 8
#define PUL1 9
#define ENA1 7


#define DIR2 4
#define PUL2 3
#define ENA2 5

char t;
bool mode = false;
bool runAllowed = false;

int wheelRadius = 44.2; //always in mm
float steps, stepSpeed, accel;
long autoTurnOff = 0;
long autoTurnOffTime = 30 * 1000; // in seconds

AccelStepper s1(1, PUL1,DIR1); // 1 for  AccelStepper::DRIVER 
AccelStepper s2(1, PUL2, DIR2); // 1 for  AccelStepper::DRIVER 

void setup(){  
    Serial.begin(9600);
    Serial.println("This B starts!");
    s1.setEnablePin(ENA1);
    s2.setEnablePin(ENA2);
    s1.setPinsInverted(false,false,true);
    s2.setPinsInverted(false,false,true);

    //all default to max speed and acceleration
    s1.setMaxSpeed(4000.0);
    s1.setAcceleration(4000.0);
    //s1.moveTo(4000);
    
    s2.setMaxSpeed(4000.0);
    s2.setAcceleration(4000.0);
    //s2.moveTo(4000);
    disableStepper();
}

void loop(){
    if(runAllowed){
      s1.run();
      s2.run();
    }
    if((s1.distanceToGo() == 0) && (s2.distanceToGo() == 0) && (!s1.isRunning()) &&(!s2.isRunning())){
      runAllowed = false;
      //reset();
    }
    if(((millis() - autoTurnOff) > autoTurnOffTime) && (!s1.isRunning())){ // auto turn of feature
      disableStepper();
    }
    serial();
}
