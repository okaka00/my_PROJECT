#include <ESP32Servo.h> 

Servo myservo;
int servoPin = 16;  
int potPin = 13;
int ADC_Max = 4096;
char val;    // variable to read the value from the analog pin
int c =0;
int a = 0;
int b = 0;

void setup() {
    Serial.begin(115200); // initialize serial communication
  //myservo.setPeriodHertz(50);// Standard 50hz servo
  myservo.attach(servoPin);
  //myservo.write(0);
  Serial.print("hello");
  //myservo.write(0);


   //delay(3000);
}

void loop() {

  
  //val = analogRead(potPin);
 // val = map(val, 0, ADC_Max, 0, 180);
 // myservo.write(val);


myservo.write(0);//tutup
delay(2000);
myservo.write(180);//buka
delay(2000);
//myservo.write(50);
//delay(2000);



}
  
  //delay(100); 

