//#include <Arduino.h>
#define encoA 12
#define encoB 13
#define pwm 14
#define dir 27

int encoderValue = 0; // Raw encoder value
float T, times, prevT;


float eprev = 0;
float eint = 0;
float de = 0; 

float u = 0;
float enco = 0;
int e = 0;

//motor direction 
  int direction = 1;

void setup() {
  Serial.begin(115200);
  pinMode(pwm,OUTPUT);
  pinMode(dir,OUTPUT);
  pinMode(encoA,INPUT);
  pinMode(encoB,INPUT);

  digitalWrite(encoA, HIGH);
  digitalWrite(encoB, HIGH);

 attachInterrupt(digitalPinToInterrupt(encoA), updateEncoder, RISING);
 // attachInterrupt(1, updateEncoder, CHANGE);
 
}

void loop() {

  // time difference 
  prevT = times;
  times = millis();
  T = (times - prevT);

 //set target
 int target = 1000;

 //PID Contents
 float kp = 1;
 float kd = 0.0;
 float ki = 0.0;
 

 //error
 enco = encoderValue;
 e = enco - target;

 //derivative
  de = ((e - eprev)/T);

 //integral
 eint = eint + (e*T);

 //control signal [pid]
   u = (kp*e) + (ki*eint) + (kd*de);

  //motor power 
  float speed = fabs(u);
  if(speed > 100)speed = 100; 

  digitalWrite(dir, direction);
  analogWrite(pwm , speed);

  //store error
    eprev = e;   
  if(enco >= 1200){
     analogWrite(pwm , 0);
     return;
  }
  Serial.print(" error : ");
  Serial.print(e);
  Serial.print(" ");
  Serial.print(" | Speed: ");
  Serial.println(speed);
  Serial.println();

 
}

  void updateEncoder(){
  //if (digitalRead(encoA)> digitalRead(encoB))
  int b = digitalRead(encoB);
  if(b>0){
    encoderValue++;
  } 
  else{
    encoderValue-- ;
  }
  }
