void serial(){
  if(Serial.available() > 0){
     t = Serial.read();
     if(t == 'm'){
       s1.enableOutputs();
       s2.enableOutputs();
       runAllowed = true;
       
       steps = Serial.parseFloat();
       stepSpeed = Serial.parseFloat();
       
       if(mode){
        steps = (steps/(wheelRadius*2*3.14)) * 800;
       }
       Serial.print("Steps/mm moved: ");
       Serial.println(abs(steps - s1.currentPosition()));
       movement(stepSpeed,stepSpeed,steps,-1*steps);
       //reset();
       getInfo();
     }
     else if(t == 'r'){
       s1.enableOutputs();
       s2.enableOutputs();
       runAllowed = true;
       
       steps = Serial.parseFloat();
       stepSpeed = Serial.parseFloat();
       
       Serial.print("Steps/mm moved: ");
       Serial.println(abs(steps - s1.currentPosition()));
       movement(stepSpeed,stepSpeed,steps,1*steps);
     }
     else if(t == 'a'){
        accel = Serial.parseFloat();
        s1.setAcceleration(accel);
        s2.setAcceleration(accel);
        Serial.print("Acceleration set to: ");
        Serial.println(accel);
     }
     else if(t == 'n'){
       stopStepper();
       Serial.println("Stopped the Motors");
     }
     else if(t == 's'){
        Serial.println("Everything was Reset");
        reset();
        getInfo();
     }
     else if(t == 'p'){
        getInfo(); 
     }
     else if(t == 'b'){
       enableStepper();
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
