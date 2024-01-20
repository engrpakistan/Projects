int Ultrasonic() {
  //change these values accordingly
  int upperlimit = 100;
  int lowerlimit = 20;
  digitalWrite(trigPin, 0);
  delayMicroseconds(2);
  digitalWrite(trigPin, 1);
  delayMicroseconds(10);
  digitalWrite(trigPin, 0);
  timetaken = pulseIn(echoPin, 1);   // time will retured in microseconds.
  distance = timetaken * 0.034 / 2;  // speed of sound is 340m/s or 0.034cm/us.
  if (distance > lowerlimit && distance < upperlimit) {
    if (distance != 0) {
      total = total - readings[readIndex];
      readings[readIndex] = distance;
      total = total + readings[readIndex];
      readIndex = readIndex + 1;
      if (readIndex >= numReadings) {
        readIndex = 0;
      }
      average = total / numReadings;
      // Serial.print (average);
      //   Serial.print("     Distance : ");
      //   Serial.println(distance);
    }
  }

  return average;

  // // convert cm into feet and inch
  //   feet = distance*0.0328 ;
  //   inch = distance*0.3937 ;
  //     Serial.print(" Feet : ");
  //   Serial.println(feet);
}