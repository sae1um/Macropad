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
#define NUM_OF_LAYERS 3

char keys[NUM_OF_LAYERS][ROWS][COLS] = {
  {
    {'0', 'Z', 'X'},
    {'7', '8', '9'},
    {'4', '5', '6'},
    {'1', '2', '3'}
  },
  {
    {'0', 'Z', 'X'},
    {'7', '8', '9'},
    {'4', '5', '6'},
    {'1', '2', '3'}
  },
  {
    {'0', 'E', 'F'},
    {'7', '8', '9'},
    {'4', '5', '6'},
    {'1', '2', '3'}
  }
}; 

int currentLayer = 0;

byte rowPins[ROWS] = {R1, R2, R3, R4};
byte colPins[COLS] = {C1, C2, C3};
Keypad keypad = Keypad(makeKeymap(keys[currentLayer]), rowPins, colPins, ROWS, COLS);

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
  void changeLayer();
  void detectKeypadPress();

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
  char keyPressed = keypad.getKey();
  if (keyPressed) {
    Serial.println(keyPressed);
    if(keyPressed == 'Z' || keyPressed == 'B' || keyPressed == 'E'){
      changeLayer();
    }else{
      detectKeypadPress(keyPressed);
    }
    Serial.println("Pressed");
  }
  detectButtonPress();
  detectEncoderTurn();
}

void detectKeypadPress(char keyPressed){


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

void changeLayer(){
  // Changes the current layer on keypress
  // LAYER1 -> LAYER2 -> LAYER3 -> LAYER1
  //Returns remainder as the new layer to loop e.g. (0+1) % 3 = 1
  currentLayer = (currentLayer + 1) % NUM_OF_LAYERS;
  // Set the new layer
  keypad.begin(makeKeymap(keys[currentLayer]));
  Serial.print("Layer Changing to Layer ");
  Serial.println(currentLayer + 1);
}
