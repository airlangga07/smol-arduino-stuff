const int sensorPin = A0;
const float baseLineTemp = 26.0;
const float baseLineThreshold = 1;

void setup() {
  Serial.begin(9600);

  for (int pinNumber = 2; pinNumber < 5; pinNumber++) {
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
}

void loop() {
  int sensorVal = analogRead(sensorPin);
  Serial.print("Sensor value: ");
  Serial.print(sensorVal);

  // convert the ADC reading to voltage
  float voltage = (sensorVal/1024.0) * 5.0;
  Serial.print(", volts: ");
  Serial.print(voltage);

  // convert the voltage to temperature in degrees
  float temperature = (voltage - .5) * 100;
  Serial.print(", temperature: ");
  Serial.println(temperature);

  if (temperature < baseLineTemp) {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  } else if (temperature >= baseLineTemp + (baseLineThreshold * 1) && temperature < baseLineTemp + (baseLineThreshold * 2)) {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  } else if (temperature >= baseLineTemp + (baseLineThreshold * 2) && temperature < baseLineTemp + (baseLineThreshold * 3)) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  } else {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
  }

  delay(1);
}
