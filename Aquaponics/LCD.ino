void LCD(int temper, float pHValue, int soilMoisture, int distance) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(temper);
  lcd.print("C");

  lcd.setCursor(10, 0);
  lcd.print("PH:");
  lcd.print(pHValue);


  lcd.setCursor(0, 1);
  lcd.print("PLANT:");
  lcd.print(soilMoisture);
  lcd.print("%");

  lcd.setCursor(9, 1);
  lcd.print("Aqua:");
  lcd.print(distance);
}