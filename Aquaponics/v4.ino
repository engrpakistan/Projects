#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP32Servo.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <WebServer.h>
//WEB
/* Put your SSID & Password */
const char* ssid = "Maaz";          // Enter SSID here
const char* password = "10922003";  //Enter Password here
/* Put IP Address details */
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
WebServer server(80);
uint8_t builtInLEDPin = 5;  // Use GPIO 2 for the built-in LED
bool builtInLEDStatus = LOW;

// Set the LCD address and dimensions
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int LED_BUILTIN = 2;

// ultrasonic
#define echoPin 19
#define trigPin 18

long timetaken;
double feet, inch;

//smoothing
const int numReadings = 8;
int readings[numReadings];  // the readings from the analog input
int readIndex = 0;          // the index of the current reading
int total = 0;              // the running total
int average = 0;

// rtc
RTC_DS3231 rtc;

// servo
// int button = ; //  use button if there is any pin avaliable
// Servo myservo;
// int pos = 0;
// int servoPin = 36;

// relay
const int LED_PIN = 5;  // GPIO pin connected to the relay module
const int SOIL_PIN = 32;

// soil
const int MOISTURE_PIN = 33;

// ph
int PHpin = 35;  // you can use A0 also
float calibration_value = 21.34 - 0.7;
int phval = 0;
unsigned long int avgval;
int buffer_arr[10], temp;
float ph_act;

// temp
#define ONE_WIRE_BUS 23
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
// millis
long previousTime_1 = 0;
long previousTime_2 = 0;
long previousTime_3 = 0;
long previousTime_4 = 0;
long previousTime_5 = 0;
long previousTime_6 = 0;
int temper;
int distance;
int soilMoisture;
float pHValue;
void setup() {
  Serial.begin(115200);
  Serial.print("test");
  pinMode(SOIL_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  analogReadResolution(12);
  //web

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);

  server.on("/", handle_OnConnect);
  server.on("/ledon", handle_builtInLEDOn);
  server.on("/ledoff", handle_builtInLEDOff);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");



  // ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }

  // rtc
  Wire.begin();
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
  }
  // rtc.adjust(DateTime(2023, 8, 17, 13, 43, 0));  //set time from HERE

  // lcd
  lcd.init();
  lcd.setBacklight(HIGH);
  lcd.print("KHIRD SOLUTION");



  // Set LED pin as OUTPUT
  pinMode(LED_BUILTIN, OUTPUT);

  // temp
  sensors.begin();

  // servo
  // ESP32PWM::allocateTimer(0);
  // ESP32PWM::allocateTimer(1);
  // ESP32PWM::allocateTimer(2);
  // ESP32PWM::allocateTimer(3);
  // myservo.setPeriodHertz(50);  // standard 50 hz servo
  // myservo.attach(servoPin, 1000, 2000);
}
void loop() {
  unsigned long currentTime = millis();
  if (currentTime - previousTime_1 >= 2000) {
    LCD(temper, pHValue, soilMoisture, distance);
    previousTime_1 = currentTime;
  }
  if (currentTime - previousTime_6 >= 3000) {
    RTC();
    previousTime_6 = currentTime;
  }
  if (currentTime - previousTime_2 >= 30000) {
    temper = Temp();
    previousTime_2 = currentTime;
  }
  if (currentTime - previousTime_3 >= 30000) {
    distance = Ultrasonic();
    previousTime_3 = currentTime;
  }
  if (currentTime - previousTime_4 >= 1000) {
    soilMoisture = Soil();
    previousTime_4 = currentTime;
  }
  //PH
  if (currentTime - previousTime_5 >= 120000) {
    pHValue = ph();
    previousTime_5 = currentTime;
  }
  //WEB
  if (currentTime - previousTime_5 >= 1000) {
    server.handleClient();
    digitalWrite(builtInLEDPin, builtInLEDStatus);  // Update the built-in LED status
  }
}


void handle_OnConnect() {
  builtInLEDStatus = LOW;
  Serial.println("Built-in LED Status: OFF");
  server.send(200, "text/html", SendHTML(builtInLEDStatus));
}

void handle_builtInLEDOn() {
  builtInLEDStatus = HIGH;
  Serial.println("Built-in LED Status: ON");
  server.send(200, "text/html", SendHTML(builtInLEDStatus));
}

void handle_builtInLEDOff() {
  builtInLEDStatus = LOW;
  Serial.println("Built-in LED Status: OFF");
  server.send(200, "text/html", SendHTML(builtInLEDStatus));
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}

String SendHTML(uint8_t ledStat) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>LED Control</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr += ".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr += ".button-on {background-color: #3498db;}\n";
  ptr += ".button-on:active {background-color: #2980b9;}\n";
  ptr += ".button-off {background-color: #34495e;}\n";
  ptr += ".button-off:active {background-color: #2c3e50;}\n";
  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>ESP32 Web Server</h1>\n";
  ptr += "<h3>Using Access Point(AP) Mode</h3>\n";

  if (ledStat) {
    ptr += "<p>Built-in LED Status: ON</p><a class=\"button button-off\" href=\"/ledoff\">OFF</a>\n";
  } else {
    ptr += "<p>Built-in LED Status: OFF</p><a class=\"button button-on\" href=\"/ledon\">ON</a>\n";
  }

  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
