
float ph() {
  for (int i = 0; i < 10; i++) {
    buffer_arr[i] = analogRead(PHpin);
    delay(30);
  }
  for (int i = 0; i < 9; i++) {
    for (int j = i + 1; j < 10; j++) {
      if (buffer_arr[i] > buffer_arr[j]) {
        temp = buffer_arr[i];
        buffer_arr[i] = buffer_arr[j];
        buffer_arr[j] = temp;
      }
    }
  }
  avgval = 0;
  for (int i = 2; i < 8; i++)
    avgval += buffer_arr[i];
  float volt = (float)avgval / 6 * 3.4469 / 4095;
  //  Serial.println(volt);
  ph_act = -5.70 * volt + calibration_value;
  // Serial.print("PH :");
  // Serial.println(ph_act);
  return ph_act;
}