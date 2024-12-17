#ifndef LEG_H
#define LEG_H

#include <ESP32Servo.h>
#include <ServoEasing.hpp>

// int err[4][2] = {{5, 7}, {3, 3}, {0, 14}, {9, 12}}; err lama
int err[4][2] = {{6, 9}, {2, 10}, {3, 4}, {4, 0}}; //err baru
//int invKinA[10] = {29, 16, 7, 3, 6, 15, 21, 25, 28, 29};
int invKinA[3] = {90, 94, 117};  
//int invKinB[10] = {29, 27, 30, 36, 45, 57, 54, 50, 44, 37};
int invKinB[3] = {26, 43, 40};

//leg 1 - OKE SUDA --> angle leg 4
int invKinL1A[5] ={80, 73, 94, 67,61 };//stand-raise-foward-backward  
int invKinL1B[5] = {40, 44, 46, 32, 27};

//leg 2 -- angle leg 3
int invKinL2A[5] = {80, 70, 73, 88,92};  //stand-raise-foward-backward
int invKinL2B[5] = {40, 50, 25, 52,57 };

//leg 3 -- angle leg 2 
int invKinL3A[5] = {80, 70, 73, 88,92};  //stand-raise-foward-backward
int invKinL3B[5] = {40, 50, 25, 52,57 };

//leg 4 - OKE SUDA -- angle leg 1
int invKinL4A[5] ={80, 69, 94, 67,61 };  //stand-raise-foward-backward
int invKinL4B[5] ={40, 51, 46, 32, 27}; //75,73,88 26,49,53


int staticArrayA[2] = {90, 75};
int staticArrayB[2] = {30, 45};

int pos1, pos2, pos3, pos4 ,pos5, pos6, pos7, pos8 = 0;

// ServoEasing LEG1S1;
// ServoEasing LEG1S2;

// ServoEasing LEG2S1;
// ServoEasing LEG2S2;

// ServoEasing LEG3S1;
// ServoEasing LEG3S2;

// ServoEasing LEG4S1;
// ServoEasing LEG4S2;

//--------------------------------

Servo LEG1S1;
Servo LEG1S2;

Servo LEG2S1;
Servo LEG2S2;

Servo LEG3S1;
Servo LEG3S2;

Servo LEG4S1;
Servo LEG4S2;

#define LEG1PIN1 32
#define LEG1PIN2 33

#define LEG2PIN1 25
#define LEG2PIN2 26

#define LEG3PIN1 19
#define LEG3PIN2 18

#define LEG4PIN1 17
#define LEG4PIN2 16

#define SERVO_MIN_PULSE 500
#define SERVO_MAX_PULSE 2500
#define SERVO_HERTZ 300

void setupLeg() {
  //ledcAttachChannel(LEG1PIN1, SERVO_HERTZ, 8, 0);
  //ledcAttachChannel(LEG1PIN2, SERVO_HERTZ, 8, 1);

  //  LEG1S1.setEasingType(EASE_CUBIC_IN_OUT);
  //  LEG1S2.setEasingType(EASE_CUBIC_IN_OUT);

  //  LEG2S1.setEasingType(EASE_CUBIC_IN_OUT);
  //  LEG2S2.setEasingType(EASE_CUBIC_IN_OUT);

  //  LEG3S1.setEasingType(EASE_CUBIC_IN_OUT);
  //  LEG3S2.setEasingType(EASE_CUBIC_IN_OUT);

  //  LEG4S1.setEasingType(EASE_CUBIC_IN_OUT);
  //  LEG4S2.setEasingType(EASE_CUBIC_IN_OUT);

  LEG1S1.setPeriodHertz(SERVO_HERTZ);
  LEG1S2.setPeriodHertz(SERVO_HERTZ);

  LEG2S1.setPeriodHertz(SERVO_HERTZ);
  LEG2S2.setPeriodHertz(SERVO_HERTZ);

  LEG3S1.setPeriodHertz(SERVO_HERTZ);
  LEG3S2.setPeriodHertz(SERVO_HERTZ);

  LEG4S1.setPeriodHertz(SERVO_HERTZ);
  LEG4S2.setPeriodHertz(SERVO_HERTZ);

  LEG1S1.attach(LEG1PIN1, SERVO_MIN_PULSE, SERVO_MAX_PULSE);
  LEG1S2.attach(LEG1PIN2, SERVO_MIN_PULSE, SERVO_MAX_PULSE);

  LEG2S1.attach(LEG2PIN1, SERVO_MIN_PULSE, SERVO_MAX_PULSE);
  LEG2S2.attach(LEG2PIN2, SERVO_MIN_PULSE, SERVO_MAX_PULSE);

  LEG3S1.attach(LEG3PIN1, SERVO_MIN_PULSE, SERVO_MAX_PULSE);
  LEG3S2.attach(LEG3PIN2, SERVO_MIN_PULSE, SERVO_MAX_PULSE);

  LEG4S1.attach(LEG4PIN1, SERVO_MIN_PULSE, SERVO_MAX_PULSE);
  LEG4S2.attach(LEG4PIN2, SERVO_MIN_PULSE, SERVO_MAX_PULSE);
}

void readyLeg() {
  LEG1S1.write(80 + err[0][0]);
  LEG1S2.write(40 + err[0][1]);

  LEG2S1.write((80 * 270 / 180) + err[1][0]); //kana tambah 8
  LEG2S2.write((40 * 270 / 180) + err[1][1]); //kana tambah 8

  LEG3S1.write(80 + err[2][0]);
  LEG3S2.write(40 + err[2][1]);

  LEG4S1.write(80 + err[3][0]); //120
  LEG4S2.write(40 + err[3][1]); //75
}

void standLeg() {
  LEG1S1.write(90 + err[0][0]);
  LEG1S2.write(30 + err[0][1]);

  LEG2S1.write(135 + err[1][0]);
  LEG2S2.write(45 + err[1][1]);

  LEG3S1.write(90 + err[2][0]);
  LEG3S2.write(30 + err[2][1]);

  LEG4S1.write(90 + err[3][0]);
  LEG4S2.write(30 + err[3][1]);
}

void staticLeg(int index) {
  LEG1S1.write(staticArrayA[index] + err[0][0]);
  LEG1S2.write(staticArrayB[index] + err[0][1]);

  LEG2S1.write((staticArrayA[index] * 270 / 180) + err[1][0]);
  LEG2S2.write((staticArrayB[index] * 270 / 180) + err[1][1]);

  LEG3S1.write(staticArrayA[index] + err[2][0]);
  LEG3S2.write(staticArrayB[index] + err[2][1]);

  LEG4S1.write(staticArrayA[index] + err[3][0]);
  LEG4S2.write(staticArrayB[index] + err[3][1]);
}

void standby(){
  LEG1S1.write(60 + err[0][0]);
  LEG1S2.write(60 + err[0][1]);

  LEG2S1.write(90 + err[1][0]);
  LEG2S2.write(90 + err[1][1]);

  LEG3S1.write(60 + err[2][0]);
  LEG3S2.write(60 + err[2][1]);

  LEG4S1.write(60 + err[3][0]);
  LEG4S2.write(60 + err[3][1]);
}

void legDown(){

  pos1 = 60;
  pos2 = 60;
  pos3 = 90;
  pos4 = 90;
  pos5 = 60;
  pos6 = 60;
  pos7 = 60;
  pos8 = 60;

  for(pos3; pos3<=135 ; pos3++){
  if(pos3<=120){
  
      LEG1S1.write(pos1 + err[0][0]);
      LEG1S2.write(pos2 + err[0][1]);

      LEG3S1.write(pos5 + err[2][0]);
      LEG3S2.write(pos6 + err[2][1]);

      LEG4S1.write(pos7 + err[3][0]);
      LEG4S2.write(pos8 + err[3][1]);
  }
  LEG2S1.write(pos3 + err[1][0]);
  LEG2S2.write(pos4 + err[1][1]);
  pos1++;
  pos2--;
  pos4--;
  pos5++;
  pos6--;
  pos7++;
  pos8--;
  delay(2);
  }
}

void jump(){
  readyLeg();
  delay(1000);
  standby();
  delay(1000);
  legDown();
  delay(200);
  standby();
  delay(1000);
}

void L1Move(int index) {
  
  LEG1S1.write(invKinA[index] + err[0][0]);
  LEG1S2.write(invKinB[index] + err[0][1]);
}

void L2Move(int index) {
  LEG2S1.write((invKinA[2 - index] * 270 / 180) + err[1][0]);
  LEG2S2.write((invKinB[2 - index] * 270 / 180) + err[1][1]);
}

void L3Move(int index) {
  LEG3S1.write(invKinA[2 - index] + err[2][0]);
  LEG3S2.write(invKinB[2 - index] + err[2][1]);
}

void L4Move(int index) {
  LEG4S1.write(invKinA[index] + err[3][0]);
  LEG4S2.write(invKinB[index] + err[3][1]);
}

//new movement
void newL1Move(int index) {
  
  LEG1S1.write(invKinL1A[index] + err[0][0]);
  LEG1S2.write(invKinL1B[index] + err[0][1]);
}

void newL2Move(int index) {
  LEG2S1.write((invKinL2A[index] * 270 / 180) + err[1][0]);
  LEG2S2.write((invKinL2B[index] * 270 / 180) + err[1][1]);
}

void newL3Move(int index) {
  LEG3S1.write(invKinL3A[index] + err[2][0]);
  LEG3S2.write(invKinL3B[index] + err[2][1]);
}

void newL4Move(int index) {
  LEG4S1.write(invKinL4A[index] + err[3][0]);
  LEG4S2.write(invKinL4B[index] + err[3][1]);

  pos1 = invKinL1A[0];
  pos2 = invKinL1B[0];
  pos3 = invKinL2A[0];
  pos4 = invKinL2B[0];
  pos5 = invKinL3A[0];
  pos6 = invKinL3B[0];
  pos7 = invKinL4A[0];
  pos8 = invKinL4B[0];

}

void initialLift(){
   pos1 = invKinL1A[0];
   pos2 = invKinL1B[0];
   pos5 = invKinL3A[0];
   pos6 = invKinL3B[0];


  for(pos1; pos1>= invKinL1A[1]; pos1-=1){
    if(pos1>=76){
      LEG1S2.write(pos2 + err[0][1]);
      LEG3S2.write(pos6 + err[1][1]);
    }
    LEG3S1.write(pos1 + err[0][0]);
    LEG3S1.write(pos5 + err[1][0]);

    pos2++;
    pos5--;
    pos6++;
    delay(10);
  }
 }

void FL13B(){
   pos1 = invKinL1A[1];
   pos2 = invKinL1B[1];
   pos5 = invKinL3A[1];
   pos6 = invKinL3B[1];

   pos3 = invKinL2A[0];
   pos4 = invKinL2A[0];
   pos7 = invKinL2A[0];
   pos8 = invKinL2A[0];

  for(pos1; pos1<=invKinL1A[2]; pos1+=1){
    if(pos1<=69){
      LEG3S1.write(pos5 + err[1][0]);
    }
    LEG1S1.write(pos1 + err[0][0]);
    LEG1S2.write(pos2 + err[0][1]);
    LEG3S2.write(pos6 + err[1][1]);

    pos2++;
    pos5++;
    pos6++;
    delay(10);
  }
}

void FL13C(){
  pos1 = invKinL1A[2];
  pos2 = invKinL1B[2];
  pos5 = invKinL3A[2];
  pos6 = invKinL3B[2];


  for(pos1; pos1>=invKinL1A[3]; pos1-=1 ){
    if(pos1<=79){
      LEG1S2.write(pos2 + err[0][1]);
      LEG3S1.write(pos6 + err[1][0]);
    }
    LEG1S1.write(pos1 + err[0][0]);
    LEG3S1.write(pos5 + err[1][0]);

    pos2--;
    pos5++;
    pos6++;
    delay(10);
  }
}

void FL13D(){
  pos1 = invKinL1A[3];
  pos2 = invKinL1B[3];
  pos5 = invKinL3A[3];
  pos6 = invKinL3B[3];

  for(pos1; pos1>=invKinL1A[4]; pos1-=1){
    LEG1S1.write(pos1 + err[0][0]);
    LEG1S2.write(pos2 + err[0][1]);
    LEG3S1.write(pos5 + err[1][0]);
    LEG3S2.write(pos6 + err[1][1]);

    pos2--;
    pos5++;
    pos6++;
    delay(10);
  }
}

void f1(){
  /*LEG1S1.write(invKinL1A[1]);
  LEG1S2.write(invKinL1B[1]);
  LEG3S1.write(invKinL3A[1]);
  LEG3S2.write(invKinL3B[1]);
  delay(500);
  LEG1S1.write(invKinL1A[2]);
  LEG1S2.write(invKinL1B[2]);
  LEG3S1.write(invKinL3A[2]);
  LEG3S2.write(invKinL3B[2]);
  delay(500);*/
  LEG1S1.write(invKinL1A[3]);
  LEG1S2.write(invKinL1B[3]);
  LEG3S1.write(invKinL3A[3]);
  LEG3S2.write(invKinL3B[3]);
 /* delay(500);
  LEG1S1.write(invKinL1A[4]);
  LEG1S2.write(invKinL1B[4]);
  LEG3S1.write(invKinL3A[4]);
  LEG3S2.write(invKinL3B[4]);
  delay(500);*/
}
void movement(){
 // FL13A();
  FL13B();
  FL13C();
  FL13D();
}

void F12(){
  LEG1S1.write(invKinL1A[1]);
  LEG1S2.write(invKinL1B[1]);
  delay(200);
  LEG1S1.write(invKinL1A[2]);
  LEG1S2.write(invKinL1B[2]);
}

void F78(){
  LEG4S1.write(invKinL4A[1]);
  LEG4S2.write(invKinL4B[1]);
  delay(200);
  LEG4S1.write(invKinL4A[2]);
  LEG4S2.write(invKinL4B[2]);
}

void F34(){
  LEG2S1.write(invKinL2A[1]* 270 / 180);
  LEG2S2.write(invKinL2B[1]* 270 / 180);
  delay(200);
  LEG2S1.write(invKinL2A[2]* 270 /180);
  LEG2S2.write(invKinL2B[2]* 270 / 180);
}

void F56f(){
  LEG3S1.write(invKinL3A[1]);
  LEG3S2.write(invKinL3B[1]);
  delay(200);
  LEG3S1.write(invKinL3A[2]);
  LEG3S2.write(invKinL3B[2]);
  LEG1S1.write(invKinL1A[3]);
  LEG1S2.write(invKinL1B[3]);
  LEG2S1.write(invKinL2A[3]* 270 / 180);
  LEG2S2.write(invKinL2B[3]* 270 / 180);
  LEG4S1.write(invKinL4A[3]);
  LEG4S2.write(invKinL4B[3]);
  delay(300);
  LEG3S1.write(invKinL3A[3]);
  LEG3S2.write(invKinL3B[3]);
}

void CRAWL(){
   F12();
   delay(500);   
   F78();
   delay(500);
   F34();
   delay(500);
   F56f();
   delay(500);
}

void sus(){
  standLeg();
  delay(2000);
  readyLeg();
  delay(2000);
}

#endif
