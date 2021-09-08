void serial(){
  if(Serial.available() > 0){
     t = Serial.read();
     if(t == 'm'){
       runAllowed = true;
       
       float steps = Serial.parseFloat();
       float stepSpeed = Serial.parseFloat();
       //float dir = Serial.parseFloat();
       if(mode){
        steps = (steps/(wheelRadius*2*3.14)) * 200;
       }
       Serial.print("Moving to: ");
       Serial.println(steps);
       forwardBackward(steps,stepSpeed);
     }
  }
     else if(t == 'r'){
       runAllowed = true;
       
       float steps = Serial.parseFloat();
       float stepSpeed = Serial.parseFloat();
       //float dir = Serial.parseFloat();
       Serial.print("Rotating");
       rotation(steps,stepSpeed);
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
