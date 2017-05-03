
const int analogPin = 0;    // the pin that the potentiometer is attached to
const int ledCount = 10;    // the number of LEDs in the bar graph

int ledPins[] = {11,10,9,8,7,6,5,4,3,2}; //Digital pins for the led lights, first green bulb is #11

void setup() {
  Serial.begin(9600);//sets the baud rate
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT);
  }}

void loop() {
  //This is the code to light up LED's
  int sensorReading = analogRead(analogPin);
  Serial.println(sensorReading);

  int ledLevel = map(sensorReading, 100, 2000, 0, ledCount); //100ppm to 2000ppm, 2000ppm is high Co2 can cause drowsiness and is poor air


  for (int thisLed = 0; thisLed < ledCount; thisLed++) {

    if (thisLed < ledLevel) {
      digitalWrite(ledPins[thisLed], HIGH);
    }

    else {
      digitalWrite(ledPins[thisLed], LOW);
    }  
  }
  Serial.print("led Level: ");
  Serial.println(ledLevel);
}
