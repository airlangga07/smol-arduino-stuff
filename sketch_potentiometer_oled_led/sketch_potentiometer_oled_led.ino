#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSansBoldOblique18pt7b.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// potentiometer definition
int const potPin = A0;
int potVal;
int ledVal;

// LED
const int redLEDPin = 10;
const int blueLEDPin = 11;
const int greenLEDPin = 9;

void setup() {
  Serial.begin(9600);

  // LED setup
  pinMode(greenLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.display();
  delay(2000); // Pause for 2 seconds
  display.clearDisplay();
}

void loop() {
  potVal = analogRead(potPin);
  Serial.print("potVal: ");
  Serial.println(potVal);

  ledVal = potVal / 4;
  
  analogWrite(redLEDPin, ledVal);
  analogWrite(blueLEDPin, ledVal);
  analogWrite(greenLEDPin, ledVal);

  testdrawstyles(potVal);
  delay(50);
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
