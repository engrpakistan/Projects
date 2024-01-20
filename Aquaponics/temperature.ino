// float Temp() {
//   sensors.requestTemperatures();
//   float temperature = sensors.getTempCByIndex(0);
//   // Serial.print("Temperature: ");
//   // Serial.print(temperature);
//   // Serial.print("C   ");
//   // Serial.print("|||");
//   return temperature;
//   // if (temperature > 35) {
//   //   Serial.println("ALERT TEMPERATURE TOO HIGH");
//   // }
// }
int Temp() {
  sensors.requestTemperatures();
 int temperature = sensors.getTempCByIndex(0);
  return temperature;
  // if (temperature > 35) {
  //   Serial.println("ALERT TEMPERATURE TOO HIGH");
  // }
}