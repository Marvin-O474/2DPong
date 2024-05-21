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
const int displaySegment_A = 0; //for the 7 segment display. This may not be necessary during physical implementation
const int led_chipCount = 4; //number of led shift registers


//constructors 
shiftOutX reg(led_latchpin, led_datapin,led_clockpin , MSBFIRST, led_chipCount); 
HC595 ledArray(led_chipCount,led_latchpin,led_clockpin,led_datapin);

/*Initializing all game variables to zero*/
int game_live = 0;

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

 //starting sequence 
  starting_chime();
  display(0);
  ledStartSequence();



}

void loop() {
game_live = 9;
int current_gameLive = 0;
game_live = current_gameLive;

while (current_gameLive > 0) 
{
  display(current_gameLive);
  long startPosition = random(2);
  if (startPosition == 0)
  {
    reg.pinOn(shPin1);
  }
  if (startPosition == 1)
  {
    reg.pinOn(shPin32);
  }

  

}




}

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
  digit = B10000011;
  digitalWrite(display_latchpin, LOW);
  shiftOut(display_datapin , display_clockpin , MSBFIRST , digit);
  digitalWrite(display_latchpin, HIGH);
  digitalWrite(displaySegment_A, LOW); //This may not be necessary during physical implementation
  }
  if (digit == 1){
  digit= B10011111;
  digitalWrite(display_latchpin, LOW);
  shiftOut(display_datapin , display_clockpin , MSBFIRST , digit);
  digitalWrite(display_latchpin, HIGH);
  digitalWrite(displaySegment_A, HIGH); //This may not be necessary during physical implementation
  }
  if (digit == 2){
  digit= B10100101;
  digitalWrite(display_latchpin, LOW);
  shiftOut(display_datapin , display_clockpin , MSBFIRST , digit);
  digitalWrite(display_latchpin, HIGH);
  digitalWrite(displaySegment_A, LOW); //This may not be necessary during physical implementation
  }
  if (digit == 3){
  digit= B10001101;
  digitalWrite(display_latchpin, LOW);
  shiftOut(display_datapin , display_clockpin , MSBFIRST , digit);
  digitalWrite(display_latchpin, HIGH);
  digitalWrite(displaySegment_A, LOW); //This may not be necessary during physical implementation
  }
  if (digit == 4){
  digit= B10011001;
  digitalWrite(display_latchpin, LOW);
  shiftOut(display_datapin , display_clockpin , MSBFIRST , digit);
  digitalWrite(display_latchpin, HIGH);
  digitalWrite(displaySegment_A, HIGH); //This may not be necessary during physical implementation
  }
  if (digit == 5){
  digit= B11001001;
  digitalWrite(display_latchpin, LOW);
  shiftOut(display_datapin , display_clockpin , MSBFIRST , digit);
  digitalWrite(display_latchpin, HIGH);
  digitalWrite(displaySegment_A, LOW); //This may not be necessary during physical implementation
  }
   if (digit == 6){
  digit= B11000001;
  digitalWrite(display_latchpin, LOW);
  shiftOut(display_datapin , display_clockpin , MSBFIRST , digit);
  digitalWrite(display_latchpin, HIGH);
  digitalWrite(displaySegment_A, LOW); //This may not be necessary during physical implementation
  }
  if (digit == 7){
  digit= B10011111;
  digitalWrite(display_latchpin, LOW);
  shiftOut(display_datapin , display_clockpin , MSBFIRST , digit);
  digitalWrite(display_latchpin, HIGH);
  digitalWrite(displaySegment_A, LOW); //This may not be necessary during physical implementation
  }
  if (digit == 8){
  digit= B10000001;
  digitalWrite(display_latchpin, LOW);
  shiftOut(display_datapin , display_clockpin , MSBFIRST , digit);
  digitalWrite(display_latchpin, HIGH);
  digitalWrite(displaySegment_A, LOW); //This may not be necessary during physical implementation
  }
  if (digit == 9){
  digit= B10001001;
  digitalWrite(display_latchpin, LOW);
  shiftOut(display_datapin , display_clockpin , MSBFIRST , digit);
  digitalWrite(display_latchpin, HIGH);
  digitalWrite(displaySegment_A, LOW); //This may not be necessary during physical implementation
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
