/*
  Button

  Turns on and off a light emitting diode(LED) connected to digital pin 13,
  when pressing a pushbutton attached to pin 2.

  The circuit:
  - LED attached from pin 13 to ground
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground

  - Note: on most Arduinos there is already an LED on the board
    attached to pin 13.

  created 2005
  by DojoDave <http://www.0j0.org>
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Button
*/

// https://www.luisllamas.es/debounce-interrupciones-arduino/ debounce por hardware
// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
const int timeThreshold = 200;

boolean encendido = false;
long timeCounter = 0;

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(buttonPin),botonPulsado,HIGH);
}


void botonPulsado(){
  
  if(millis() > timeCounter + timeThreshold){
    timeCounter = millis();
    encendido = !encendido;
    Serial.println("Pulsado!");    
  }
  

}


void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  
  if(encendido){
    digitalWrite(ledPin, HIGH);
  }else{
   digitalWrite(ledPin, LOW); 
  }
}
