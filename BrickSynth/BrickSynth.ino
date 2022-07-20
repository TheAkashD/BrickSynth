//new bootloader - disconnect arduino before uploading
#include <MozziGuts.h>
#include <Oscil.h>
#include <pitches.h>
#include <tables/sin2048_int8.h> //generic sine function

// Mozzi Library
/* https://sensorium.github.io/Mozzi/learn/a-simple-sketch/ */

//D1 - D5  =>  ROWS
//D6 - D10 =>  COLS
//A0 - A5  =>  POTS

//for multiple channels (polyphonic) create multiple oscillators (8 ?)

#define pot0 A0
#define pot1 A1
#define pot2 A2
#define pot3 A3
#define pot4 A4
#define pot5 A5

#define r1 1
#define r2 2
#define r3 3
#define r4 4
#define r5 5

#define c1 6
#define c2 7
#define c3 8
#define c4 9
#define c5 10

//int rows[] = {0,1,2,3,4};  //input
//int cols[] = {5,6,7,8,9}; //output (don't use 9 for mozzi)
byte switchPin[10] = {r1,r2,r3,r4,r5,c1,c2,c3,c4,c5};
byte switchValue[42];
//#define speakerL 9
//#define speakerR 9 //ATTACH BOTH TO PIN 9 for MOZZI

int potVal0, potVal1, potVal2, potVal3, potVal4, potVal5;
unsigned int thisPitch;

void setup() 
{
  Serial.begin(9600); //debugging and communications
  //Serial1.begin(9600); //Bluetooth RX/TX 

  pinMode(pot0, INPUT);
  pinMode(pot1, INPUT);
  pinMode(pot2, INPUT);
  pinMode(pot3, INPUT);
  pinMode(pot4, INPUT);
  pinMode(pot5, INPUT);

//  pinMode(r1, INPUT_PULLUP);
//  pinMode(r2, INPUT_PULLUP);
//  pinMode(r3, INPUT_PULLUP);
//  pinMode(r4, INPUT_PULLUP);
//  pinMode(r5, INPUT_PULLUP);
//
//  pinMode(c1, OUTPUT);
//  pinMode(c2, OUTPUT);
//  pinMode(c3, OUTPUT);
//  pinMode(c4, OUTPUT);
//  pinMode(c5, OUTPUT);

//  pinMode(speakerL, OUTPUT);
//  pinMode(speakerR, OUTPUT);
}

void updateControl(){
}

int updateAudio(){
  //return aSin.next();
}

void loop() 
{
  potVal0 = mozziAnalogRead(pot0);
  potVal1 = mozziAnalogRead(pot1);
  potVal2 = mozziAnalogRead(pot2);
  potVal3 = mozziAnalogRead(pot3);
  potVal4 = mozziAnalogRead(pot4);
  potVal5 = mozziAnalogRead(pot5);
  
  thisPitch = map(potVal0, 400, 1000, 120, 1500); //TEMP
  //Serial.println(digitalRead(5));
  //noTone(speakerR);
//  tone(speakerL, thisPitch);
//  tone(speakerR, thisPitch);

  //reading keys
  byte n = 0;
  for (byte i = 0; i <= 10; i++) {
    pinMode(switchPin[i], OUTPUT);
    digitalWrite(switchPin[i], LOW);
    for (byte j = 0; j <= 10; j++) {
      if (j != i) {
        switchValue[n++] = digitalRead(switchPin[j]);
        Serial.println(digitalRead(switchPin[j]));
      }
    }
    pinMode(switchPin[i], INPUT_PULLUP);
  }
  
  delay(1); //generic processing delay of 1 ms

  audioHook();
}

/*
Potentiometer Functions List
1 - Volume
2 - Phaser Amount ("weight")
3 - Phaser Speed
4 - Flanger
5 - Pitch Bend/Distortion
6 - Waveform alteration
*/
