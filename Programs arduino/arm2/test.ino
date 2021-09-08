void mofo(){
  int i;
  enableStepper();
  digitalWrite(DirX, LOW);
  digitalWrite(DirY, LOW);
  for(i = 0;i<400;i++){
      digitalWrite(StepX,HIGH);
      digitalWrite(StepY,HIGH);
      delayMicroseconds(1000);
      digitalWrite(StepX,LOW); 
      digitalWrite(StepY,LOW);
      delayMicroseconds(1000);
    }
    digitalWrite(DirX, LOW);
    for(i = 0;i<200;i++){
      digitalWrite(StepX,HIGH);
      //digitalWrite(StepY,HIGH);
      delayMicroseconds(1000);
      digitalWrite(StepX,LOW); 
      //digitalWrite(StepY,LOW);
      delayMicroseconds(1000);
    }
    digitalWrite(DirX, HIGH);
    for(i = 0;i<200;i++){
      digitalWrite(StepX,HIGH);
      //digitalWrite(StepY,HIGH);
      delayMicroseconds(1000);
      digitalWrite(StepX,LOW); 
      //digitalWrite(StepY,LOW);
      delayMicroseconds(1000);
    }
    
    digitalWrite(DirX, HIGH);
    digitalWrite(DirY,HIGH);
    for(i = 0;i<400;i++){
      digitalWrite(StepX,HIGH);
      digitalWrite(StepY,HIGH);
      delayMicroseconds(1000);
      digitalWrite(StepX,LOW); 
      digitalWrite(StepY,LOW);
      delayMicroseconds(1000);
    }
  }
