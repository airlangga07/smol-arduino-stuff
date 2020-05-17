#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSansBoldOblique9pt7b.h>
#include <Fonts/FreeSansBoldOblique18pt7b.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// light sensor
const int sensorPin = A0;
int sensorLow = 1023;
int sensorHigh = 0;
int lightSensorValue;

const int ledPin = 13;

void setup() {
  Serial.begin(9600);
  
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V inter nally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.display();
  delay(2000); // Pause for 2 seconds
  display.clearDisplay();

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  while (millis() < 5000) {
    lightSensorValue = analogRead(A0);

    if (lightSensorValue > sensorHigh) {
      sensorHigh = lightSensorValue;
    }

    if (lightSensorValue < sensorLow) {
      sensorLow = lightSensorValue;
    }
  }

  digitalWrite(ledPin, LOW);
}

void loop() {
  lightSensorValue = analogRead(sensorPin);

  // make the sound
  int pitch = map(lightSensorValue, sensorLow, sensorHigh, 50, 4000);
  tone(8, pitch, 20);

  // draw the OLED
  testdrawstyles(lightSensorValue);

  delay(10);
}

void testdrawstyles(int x) {
  display.clearDisplay();
  display.setFont(&FreeSansBoldOblique18pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,27);
  display.println(x, DEC);
  display.display();
}
