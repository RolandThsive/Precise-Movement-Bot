void reset(){
  s1.setCurrentPosition(0);
  s2.setCurrentPosition(0);
  Serial.println("Positions Were Reset");
}

void stopStepper(){
  s1.stop();
  s2.stop();  
}
void disableStepper(){
  Serial.println("Released the Motors");
  s1.disableOutputs();   
  s2.disableOutputs();
  autoTurnOff = millis();
  //releaseAndBlock(1,1);
}
void enableStepper(){
  Serial.println("Blocked the Motors");
  s1.enableOutputs(); 
  s2.enableOutputs();  
}

void getInfo(){
  Serial.print( "Stepper 1: ");
  Serial.println(s1.currentPosition());
  Serial.print( "Stepper 1 Speed: ");
  Serial.println(s1.speed());
  
  Serial.print("Stepper 2: ");
  Serial.println(s2.currentPosition());
  Serial.print( "Stepper 2 Speed: ");
  Serial.println(s2.speed());
}


void movement(int ss1, int ss2, float steps1,float steps2){
  
  s1.setMaxSpeed(ss1);
  s2.setMaxSpeed(ss2);
  
  s1.moveTo(steps1);
  s2.moveTo(steps2);
}
