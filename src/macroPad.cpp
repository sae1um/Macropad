// Libraries
#include <Arduino.h>
#include <Keypad.h>
#include <Encoder.h>
#include "HID-Project.h"
#include <Bounce2.h>

//Key pinouts
const byte R1 = 5;
const byte R2 = 6;
const byte R3 = A3; 
const byte R4 = A2;   
const byte C1 = 7;
const byte C2 = 8;
const byte C3 = 9;

const byte ROWS = 4;
const byte COLS = 3;

char keys[ROWS][COLS] = {
  {'O', 'Z', 'X'},
  {'7', '8', '9'},
  {'4', '5', '6'},
  {'1', '2', '3'},
}; 

byte rowPins[ROWS] = {R1, R2, R3, R4};
byte colPins[COLS] = {C1, C2, C3};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

//Encoder
#define CLK 3
#define DT 2
#define SW A1
Encoder volumeKnob(CLK, DT); 
Bounce volumeButton = Bounce(SW, 10); 
int oldPosition = -999;
unsigned long lastButtonPress = 0; 

//LED pinout
#define LED1 16
#define LED2 15
#define LED3 14

// Initialising functions
void detectButtonPress();
void detectEncoderTurn();
void startupLights();
// void detectKeypadPress();

void setup(){
  Serial.begin(9600);
  Serial1.begin(9600);

  // pinMode(rowPin, OUTPUT);
  // pinMode(colPin, INPUT_PULLUP);

  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, INPUT_PULLUP);

  Keyboard.begin();
  Consumer.begin();

  startupLights();
}

void loop(){
  char customKey = keypad.getKey();
  if (customKey) {
    Serial.println(customKey);
    Serial.println("Pressed");
  }
  detectButtonPress();
  detectEncoderTurn();
  // detectKeypadPress();
}

void detectButtonPress(){
  int btnState = digitalRead(SW);

  //LOW signal, button is pressed
  if (btnState == LOW) {
    // Current time to last press
    if (millis() - lastButtonPress > 50) {
      // Serial.println("Button pressed!");
      Consumer.write(MEDIA_VOL_MUTE);
    }
    // Set last press to current time
    lastButtonPress = millis();
  }
  delay(1);
}

void detectEncoderTurn(){
  //Read current position of the encoder
  //Divide by 2 to get a more accurate reading
  long currentPosition = volumeKnob.read() / 2;
  
  // Check if the position has changed
  // If it has, check if it is a left or right turn
  if(currentPosition != oldPosition){
    if((currentPosition - oldPosition) > 0){
      Serial.println("Turned Left");
      Consumer.write(MEDIA_VOL_DOWN);
    }else{
      Serial.println("Turned Right");
      Consumer.write(MEDIA_VOL_UP);
    }
    // Update the old position to the current position
    oldPosition = currentPosition;
    delay(200);
  }
}


void startupLights(){
  //Alternate between the three LEDs
  digitalWrite(LED1, HIGH);
  delay(500);
  digitalWrite(LED1, LOW);
  delay(500);
  digitalWrite(LED2, HIGH);
  delay(500);
  digitalWrite(LED2, LOW);
  delay(500);
  digitalWrite(LED3, HIGH);
  delay(500);
  digitalWrite(LED3, LOW);
  
  delay(500);

  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  delay(500);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
}