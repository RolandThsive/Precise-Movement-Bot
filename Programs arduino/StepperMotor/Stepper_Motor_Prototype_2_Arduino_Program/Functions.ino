void forwardBackward(float steps, float speedStep){
 digitalWrite(EnPin,LOW);
 if(steps<0){
   digitalWrite(DirX, HIGH);
   digitalWrite(DirY, LOW);
 }
 else{
   digitalWrite(DirX, LOW);
   digitalWrite(DirY, HIGH);
 }
 calc = 1/speedStep * 1000000;
 stepGlobal = abs(steps);
}

void rotation(float steps, float speedStep){
  digitalWrite(EnPin,LOW);
  calc = 1/speedStep * 1000000;
  stepGlobal = abs(steps);
  if(steps < 0){
    digitalWrite(DirX, HIGH);
    digitalWrite(DirY, HIGH);
  }
  else{
    digitalWrite(DirX, LOW);
    digitalWrite(DirY, LOW);
  }
}
void disableStepper(){
  Serial.println("Released the Motors");
  digitalWrite(EnPin,HIGH);
  autoTurnOff = millis();
  //releaseAndBlock(1,1);
}
