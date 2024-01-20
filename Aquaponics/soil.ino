int Soil() {
  int value;
  int moistureValue = analogRead(MOISTURE_PIN);
  float moisturePercentage = map(moistureValue, 4095, 1400, 0, 100);

   relayControl(SOIL_PIN, HIGH);
    //relay control ... soil
  if (moisturePercentage < 30 && moisturePercentage >= 0) {
    relayControl(SOIL_PIN, LOW);
    lcd.setCursor(0, 1);
    lcd.clear();
    // lcd.print("Watering Plants :)");
  }
else if (moisturePercentage > 31 && moisturePercentage < 101) {
  relayControl(SOIL_PIN, HIGH);
}
  return moisturePercentage;
}



// //Just to turn on relay on and off not a main code 
// void  Soil() {
//   switch (ledState) {
//     case OFF: {
//       if (millis() - chrono >= delayOff) {
//         chrono = millis();
//          relayControl(SOIL_PIN, LOW);
//         ledState = ON;
//       }
//       break;
//     }
//     case ON: { 
//       if (millis() - chrono >= delayOn) {
//         chrono = millis();
//          relayControl(SOIL_PIN, HIGH);
//         ledState = OFF;
//       }
//       break;
//     }
//   }
// }


