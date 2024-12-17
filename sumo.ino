#include <NewPing.h>
#define TRIGGER_PIN1    12 //out
#define TRIGGER_PIN2    26
#define echoPin1        25 //in
#define echoPin2        27 //in
#define TRIGGER_PIN3    14 //out
#define echoPin3        13  //in
#define PING_ITERATIONS 5   // Number of pings to use for median calculation.

#define pwmA  5
#define A_in1 19
#define A_in2 18
#define pwmB  23
#define B_in1 21
#define B_in2 22
#define stdby 32
#define IR1 34 //input only pins
#define IR2 35 //input only pins
#define led1 15
#define led2 2
#define led3 4

#define pwmConst 180
#define pwmAsearch 130

#define MAX_DISTANCE 100
NewPing sonar1(TRIGGER_PIN1, echoPin1, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN2, echoPin2, MAX_DISTANCE);
NewPing sonar3(TRIGGER_PIN3, echoPin3, MAX_DISTANCE);

unsigned int uS1, uS2, uS3, dist1, dist2, dist3, ir1, ir2;
float distanceCm2;
//long duration2;
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701
const unsigned long interval = 5;
unsigned long current, previous, previous1, previous2, previous3, previous4 = 0;

static bool searching = false;
static unsigned long searchStartTime = 0;

void setup() {
  Serial.begin(115200); // Starts the serial communication
  pinMode(pwmA, OUTPUT);
  pinMode(A_in1, OUTPUT);
  pinMode(A_in2, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(B_in1, OUTPUT);
  pinMode(B_in2, OUTPUT);
  pinMode(stdby, OUTPUT);
//  pinMode(TRIGGER_PIN, OUTPUT); // Sets the trigPin as an Output
//  pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
//  pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
//  pinMode(echoPin3, INPUT); // Sets the echoPin as an Input
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  digitalWrite(stdby, HIGH);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  digitalWrite (led1, LOW);
  digitalWrite (led2, LOW);
  digitalWrite (led3, LOW);
  delay(1000);
}

void loop() {
  search();
  digitalWrite(led1,HIGH);
  digitalWrite(led2,HIGH);
  digitalWrite(led3,HIGH);

  
}

void search()
{
  current = millis();
  if (current - previous1 >= 50)
  {
    uS1 = sonar1.ping_median(PING_ITERATIONS); // Get median ping time in microseconds (uS).
    dist1 = uS1 / US_ROUNDTRIP_CM;
    previous1 = current;
  }
  //delay(50);
  if (current - previous2 >= 50)
  {
    uS2 = sonar2.ping_median(PING_ITERATIONS); // Get median ping time in microseconds (uS).
    dist2 = uS2 / US_ROUNDTRIP_CM;
    previous2 = current;
  }
  //delay(50);
  if (current - previous3 >= 50)
  {
    uS3   = sonar3.ping_median(PING_ITERATIONS); // Get median ping time in microseconds (uS).
    dist3 = uS3 / US_ROUNDTRIP_CM;
    previous3 = millis();
  }
  ir1 = digitalRead(IR1);
  ir2 = digitalRead(IR2);
  Serial.print("IR1: "); Serial.println(ir1);
  Serial.print("IR2: "); Serial.println(ir2);
  Serial.print("Ultra1: "); Serial.println(dist1);
  Serial.print("Ultra2: "); Serial.println(dist2);
  Serial.print("Ultra3: "); Serial.println(dist3); Serial.println();

  if (ir1 == 0 && ir2 == 0)
  {
    if (dist1 <= 40 && dist1 != 0)
    {
      Serial.println("dist1 <=15");
      digitalWrite(led3, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led1, HIGH);
      hitLeft();
      searching = false;
    }
    else if (dist2 <= 50 && dist2 != 0)
    {
      Serial.println("dist2 <=15");
      digitalWrite(led1, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led2, HIGH);
      hitForward();
      searching = false;
    }
    else if (dist3 <= 40 && dist3 != 0)
    {
      Serial.println("dist3 <=15");
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, HIGH);
      hitRight();
      searching = false;
    }
    else
    {
      
      Serial.println("searching....");
      hitForward();
      if (current - searchStartTime >= 500)
      {
        Serial.println("forward sikit");
              digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(A_in1, LOW);
      digitalWrite(A_in2, HIGH);
      analogWrite (pwmA, 150);
      digitalWrite(B_in1, HIGH);
      digitalWrite(B_in2, LOW);
      analogWrite (pwmB, 90);//pwmConst is 180
        searchStartTime = millis();
      }
    }
  }
  else
  {
    Serial.println("Jumpa black");
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    reverse();
  }


}
void stop()
{
  digitalWrite(A_in1, LOW);
  digitalWrite(A_in2, LOW);
  analogWrite (pwmA, 150);
  digitalWrite(B_in1, LOW);
  digitalWrite(B_in2, LOW);
  analogWrite (pwmB, 100);//pwmConst is 180
}
void hitForward()
{
  digitalWrite(A_in1  , HIGH);
  digitalWrite(A_in2  , LOW);
  analogWrite (pwmA   , 180);
  digitalWrite(B_in1  , HIGH);
  digitalWrite(B_in2  , LOW);
  analogWrite (pwmB   , 180);  //pwmConst is 180
}

void  reverse()
{
  current = millis();
  if (current - previous4 >= 1000)
  {
    digitalWrite(A_in1, LOW);
    digitalWrite(A_in2, HIGH);
    analogWrite (pwmA, 130);
    digitalWrite(B_in1, LOW);
    digitalWrite(B_in2, HIGH);
    analogWrite (pwmB, 130);
    previous4 = current;
  }
}

void hitLeft()
{
  Serial.println("Entered hit left");
  //only go left if no black line detected
  //if ir detected, reverse()
  digitalWrite(A_in1, HIGH);
  digitalWrite(A_in2, LOW);
  analogWrite (pwmA, 150);
  digitalWrite(B_in1, LOW);
  digitalWrite(B_in2, HIGH);
  analogWrite (pwmB, 100);//pwmConst is 180
  //delay(2000);
}

void hitRight()
{
  digitalWrite(A_in1, LOW);
  digitalWrite(A_in2, HIGH);
  analogWrite (pwmA, 150);
  digitalWrite(B_in1, HIGH);
  digitalWrite(B_in2, LOW);
  analogWrite (pwmB, 100);//pwmConst is 180
  //only go right if no black line detected
  //if ir detected, reverse()
}