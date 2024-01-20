
void RTC() {
  DateTime now = rtc.now();
  int hour = now.hour();
  int minute = now.minute();
  int second = now.second();

  if (hour >= 8 && hour < 20) {
    relayControl(LED_PIN, LOW);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Day");
  } else {
    relayControl(LED_PIN, HIGH);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Night");
  }
  
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  printDigits(hour);
  lcd.print(":");
  printDigits(minute);
  lcd.print(":");
  printDigits(second);
}
void printDigits(int digits) {
  // Add leading zero if the number is less than 10
  if (digits < 10) {
    lcd.print("0");
  }
  lcd.print(digits);
}
// #include <Wire.h>
// #include <RTClib.h>

// RTC_DS3231 rtc;

// void setup() {
//   Serial.begin(115200);
//   Wire.begin();
//   rtc.begin();
//   rtc.adjust(DateTime(2023, 8, 11, 4, 41, 0));

// }

// void loop() {
//   DateTime now = rtc.now();
//   int hour = now.hour();
//   int minute = now.minute();
//   int second = now.second();

//   if (hour >= 8 && hour < 20) {
//     relayControl(LED_PIN, LOW);
//     lcd.clear();
//     lcd.setCursor(16, 0);
//     lcd.print("D");
//   } else {
//     relayControl(LED_PIN, HIGH);
//     lcd.clear();
//     lcd.setCursor(16, 0);
//     lcd.print("N");
//   }

//   Serial.print("Current Time: ");
//   printDigits(hour);
//   Serial.print(":");
//   printDigits(minute);
//   Serial.print(":");
//   printDigits(second);
//   Serial.println();

//   delay(1000);  // Update every second
// }
