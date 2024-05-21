//necessary Libraries
#include "pitches.h"
#include<Arduino.h>
#include <ShiftOutX.h>
#include <ShiftPinNo.h>
#include <HC595.h>

//function prototypes
void starting_chime();
void display (int digit);
void ledStartSequence();
void gameOverSound();

//segment A of the 7 segment display is malfunctioning. 
//defining all pins used 
const int button_1 = 9;
const int button_2 = 10;
const int buzzer = 8;
const int led_datapin = 2; 
const int led_latchpin = 3;
const int led_clockpin = 4;
const int display_datapin  = 5;
const int display_latchpin  = 6;
const int display_clockpin  = 7;
const int displaySegment_A = 11; //for the 7 segment display. This may not be necessary during physical implementation
const int led_chipCount = 4; //number of led shift registers


//constructors 
shiftOutX reg(led_latchpin, led_datapin,led_clockpin , MSBFIRST, led_chipCount); 
HC595 ledArray(led_chipCount,led_latchpin,led_clockpin,led_datapin);

/*Initializing all game variables to zero*/
int game_live = 9;
int current_gameLive = 0;

//other important game variables
const unsigned long gameInterval = 20000; // speeds up te game very 20 seconds
unsigned long previousTime =0;


void setup() {
  pinMode(button_1, INPUT_PULLUP);
  pinMode(button_2, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  pinMode(led_datapin, OUTPUT);
  pinMode(led_latchpin, OUTPUT);
  pinMode(led_clockpin, OUTPUT);
  pinMode(display_datapin, OUTPUT);
  pinMode(display_latchpin, OUTPUT);
  pinMode(display_clockpin, OUTPUT);
  pinMode(displaySegment_A, OUTPUT);
//for the HC595 library
  ledArray.reset();
  randomSeed(analogRead(A0)); //initialize random number generator
  Serial.begin(9600);

// starting sequence 
  starting_chime();
  display(0);
  ledStartSequence();
  display(9);
}


void loop() {
int button1_state = digitalRead(button_1);
int button2_state = digitalRead(button_2);
int dir = 0;
int startPin = 0;
int delayMs =500;

if (button1_state == LOW){
  dir = 3;
  startPin = 1;
  tone(buzzer, 800, 50);
}
if(button2_state == LOW){
  dir = -3;
  startPin = 28;
  tone(buzzer,1000,50);
}
/*for changing the led color*/
int count = 0;

while(button1_state == LOW || button2_state == LOW){
  //updates game clock frequently 
  unsigned long currentTime = millis();

  ledArray.setPin(startPin,ON);
  ledArray.setPin(startPin - dir,OFF);
  delay(delayMs);
  int currentButton1_state = digitalRead(button_1);
  int currentButton2_state = digitalRead(button_2);
  if(currentButton1_state == LOW){
    dir = 3;
    tone(buzzer, 800, 50);
  }
  if(currentButton2_state == LOW){
    dir = -3;
    tone(buzzer,1000,50);
  }
  String stateOfAllPins = ledArray.toString();
  if(stateOfAllPins == "00000000|00000000|00000000|00000000|"){
    game_live--;
    display(game_live);
    break;
  }
  if(game_live == 0){
    gameOverSound();
    game_live = 9;
    display(game_live);
    ledArray.setPins(1,32,OFF); //Turn off all the LED's
    break;
    }

  if(currentTime - previousTime >= gameInterval && delayMs != 50){
    delayMs -= 50;
    previousTime =currentTime;
    Serial.println(delayMs);
  }
  /*To make the lED blue when the game reaches a certain speed*/
  if(delayMs == 350 && count == 0) {
    ledArray.setPin(startPin,OFF);
    startPin += 1;
    count++;
  }
  /*To make the lED red when the game reaches a certain speed*/
  if(delayMs == 200 && count == 1) {
    ledArray.setPin(startPin,OFF);
    startPin-=2;
    count++;
  }
  startPin+=dir;
}
}


/*Function implementations*/
void starting_chime(){
  tone(buzzer, NOTE_E4);
  delay(150);
  tone(buzzer, NOTE_G4);
  delay(150);
  tone(buzzer, NOTE_E5);
  delay(150);
  tone(buzzer, NOTE_C5);
  delay(150);
  tone(buzzer, NOTE_D5);
  delay(150);
  tone(buzzer, NOTE_G5);
  delay(150);
  noTone(buzzer);
}
void display (int digit){
if (digit == 0){
  digit = B01111100;
  digitalWrite(display_latchpin, LOW);
  shiftOut(display_datapin , display_clockpin , MSBFIRST , digit);
  digitalWrite(display_latchpin, HIGH);
  digitalWrite(displaySegment_A, HIGH); //This may not be necessary during physical implementation
  }
  if (digit == 1){
  digit= B01100000;
  digitalWrite(display_latchpin, LOW);
  shiftOut(display_datapin , display_clockpin , MSBFIRST , digit);
  digitalWrite(display_latchpin, HIGH);
  digitalWrite(displaySegment_A, LOW); //This may not be necessary during physical implementation
  }
  if (digit == 2){
  digit= B01011010;
  digitalWrite(display_latchpin, LOW);
  shiftOut(display_datapin , display_clockpin , MSBFIRST , digit);
  digitalWrite(display_latchpin, HIGH);
  digitalWrite(displaySegment_A, HIGH); //This may not be necessary during physical implementation
  }
  if (digit == 3){
  digit= B01110010;
  digitalWrite(display_latchpin, LOW);
  shiftOut(display_datapin , display_clockpin , MSBFIRST , digit);
  digitalWrite(display_latchpin, HIGH);
  digitalWrite(displaySegment_A, HIGH); //This may not be necessary during physical implementation
  }
  if (digit == 4){
  digit= B01100110;
  digitalWrite(display_latchpin, LOW);
  shiftOut(display_datapin , display_clockpin , MSBFIRST , digit);
  digitalWrite(display_latchpin, HIGH);
  digitalWrite(displaySegment_A, LOW); //This may not be necessary during physical implementation
  }
  if (digit == 5){
  digit= B00110110;
  digitalWrite(display_latchpin, LOW);
  shiftOut(display_datapin , display_clockpin , MSBFIRST , digit);
  digitalWrite(display_latchpin, HIGH);
  digitalWrite(displaySegment_A, HIGH); //This may not be necessary during physical implementation
  }
   if (digit == 6){
  digit= B00111110;
  digitalWrite(display_latchpin, LOW);
  shiftOut(display_datapin , display_clockpin , MSBFIRST , digit);
  digitalWrite(display_latchpin, HIGH);
  digitalWrite(displaySegment_A, HIGH); //This may not be necessary during physical implementation
  }
  if (digit == 7){
  digit= B01100000;
  digitalWrite(display_latchpin, LOW);
  shiftOut(display_datapin , display_clockpin , MSBFIRST , digit);
  digitalWrite(display_latchpin, HIGH);
  digitalWrite(displaySegment_A, HIGH); //This may not be necessary during physical implementation
  }
  if (digit == 8){
  digit= B01111110;
  digitalWrite(display_latchpin, LOW);
  shiftOut(display_datapin , display_clockpin , MSBFIRST , digit);
  digitalWrite(display_latchpin, HIGH);
  digitalWrite(displaySegment_A, HIGH); //This may not be necessary during physical implementation
  }
  if (digit == 9){
  digit= B01110110;
  digitalWrite(display_latchpin, LOW);
  shiftOut(display_datapin , display_clockpin , MSBFIRST , digit);
  digitalWrite(display_latchpin, HIGH);
  digitalWrite(displaySegment_A, HIGH); //This may not be necessary during physical implementation
  }
}

void ledStartSequence(){
int delayMs = 100;
int lastPin = ledArray.lastPin();
int followers = random(1,5);
  for(int i = 0 ; i <= lastPin ; i++) {
    ledArray.setPin(i, ON);
    if (i >= followers) ledArray.setPin(i-followers, OFF);
    delay(delayMs);
  }
  for (int i = lastPin-followers ; i <= lastPin; i++) {
    ledArray.setPin(i, OFF);
    delay(delayMs); 
  }
delay(delayMs);
uint32_t goSequence=0b00010010010010010010010010010010;
digitalWrite(led_latchpin,LOW);
shiftOut_32(led_datapin , led_clockpin , MSBFIRST , goSequence);
digitalWrite(led_latchpin,HIGH);
delay(delayMs);
reg.allOff();
}

void gameOverSound() {
// Play a Wah-Wah-Wah-Wah sound
  tone(buzzer, NOTE_DS5);
  delay(300);
  tone(buzzer, NOTE_D5);
  delay(300);
  tone(buzzer, NOTE_CS5);
  delay(300);
  for (byte i = 0; i < 10; i++) {
    for (int pitch = -10; pitch <= 10; pitch++) {
      tone(buzzer, NOTE_C5 + pitch);
      delay(5);
    }
  }
  noTone(buzzer);
  delay(500);
}


