void knob(){
        
	// Read the current state of CLK



	// If last and current state of CLK are different, then pulse occurred
	// React to only 1 state change to avoid double count
	if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){

		// If the DT state is different than the CLK state then
		// the encoder is rotating CCW so decrement
		if (digitalRead(DT) != currentStateCLK) {
			counter --;
			currentDir ="CCW";
		} else {
			// Encoder is rotating CW so increment
			counter ++;
			currentDir ="CW";
		}
    int value,mod;
    if(counter<0){
      value=counter*(-1);
    }else{
      value=counter;
    }
    mod=value%4;
   
    // conter=counter%4;
    Serial.print("mod: ");
		Serial.print(mod);
		Serial.print("| Value: ");
		Serial.print(value);
		Serial.print(" | Counter: ");
		Serial.println(counter);

    // lcd.setCursor(0,0);
    // lcd.clear();
    // lcd.print("  Counter: ");
		// lcd.print(counter);
	}
  else{
    Serial.println(" TEST counter failed");

  }

	// Remember last CLK state
	lastStateCLK = currentStateCLK;

	// Read the button state
	// int btnState = digitalRead(SW);

	// //If we detect LOW signal, button is pressed
	// if (btnState == LOW) {
	// 	//if 50ms have passed since last LOW pulse, it means that the
	// 	//button has been pressed, released and pressed again
	// 	if (millis() - lastButtonPress > 50) {
	// 		Serial.println("Button pressed!");
	// 	}

	// 	// Remember last button press event
	// 	lastButtonPress = millis();
	// }

	// Put in a slight delay to help debounce the reading
}
