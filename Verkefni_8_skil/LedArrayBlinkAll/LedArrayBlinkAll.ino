const int ledCount = 10; 

int ledPins[] = {11,10,9,8,7,6,5,4,3,2}; //Array for led pins

void setup() {
  
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT);
  }}
  
void loop() {
  for (int thisLed = 0; thisLed < ledCount; thisLed++) { //Loop through led pins
      digitalWrite(ledPins[thisLed], HIGH); //Set thisled to high
      delay(1000); //Wait 1 second
      digitalWrite(ledPins[thisLed], LOW);  //Set thisLed to low
  }
}
