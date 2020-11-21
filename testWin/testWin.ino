
#include "Keyboard.h"

#define KEY_MENU 0xED
#define SPACING_TIME 1000

const int winPin = 2;
const int optPin = 3;
volatile bool winPressed = false;
volatile bool optPressed = false;
volatile uint32_t winPtime;
volatile uint32_t optPtime;
uint32_t curTime;

void pressWin();
void pressOpt();

void setup() {
    // make pin 2 an input and turn on the pull-up resistor so it goes high unless
    // connected to ground:
    pinMode(winPin, INPUT_PULLUP);
    pinMode(optPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(winPin), pressWin,   CHANGE);
    attachInterrupt(digitalPinToInterrupt(optPin), pressOpt,   CHANGE);
    // initialize control over the keyboard:
    Keyboard.begin();
    curTime = winPtime = optPtime = micros();
}

void loop() {
    curTime = micros();
    if(winPressed && curTime > winPtime + SPACING_TIME){
        Serial.println(curTime - winPtime);
        if(digitalRead(winPin) == LOW){
            Keyboard.press(KEY_LEFT_GUI);
        }else{
            Keyboard.release(KEY_LEFT_GUI);
        }
        winPressed = false;
    }

    if(optPressed && curTime > optPtime + SPACING_TIME){
        Serial.println(curTime - optPtime);
        if(digitalRead(optPin) == LOW){
            Keyboard.press(KEY_MENU);
        }else{
            Keyboard.release(KEY_MENU);
        }
        optPressed = false;
    }

    yield();
}

void pressWin(){
    winPressed = true;
    winPtime = micros();
}
void pressOpt(){
    optPressed = true;
    optPtime = micros();
}
