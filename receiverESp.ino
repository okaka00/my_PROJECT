#include "WiFi.h"
#include "esp_now.h"

#define m1 13
#define m2 12
#define m3 14
#define m4 27
#define enA 26
#define enB 25

#define vrx_init 1895
#define vry_init 1940
#define UP_THRESHOLD    1000
#define DOWN_THRESHOLD  4000
#define left 3000
#define right 1000

int speed = 100;

// Structure for incoming data
typedef struct struct_message {
  int redValue;
  int whiteValue;
  int valueX;
  int valueY;
  int swValue;
} struct_message;

// Reading data message
struct_message readingData;

int vrx = 0;
int vry = 0; 
int red;
int white;
int val;


// Function to receive incoming data from the sender ESP32
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len){
  memcpy(&readingData, incomingData, sizeof(readingData));
  
  vry = readingData.valueY;
  vrx = readingData.valueX;
  white = readingData.whiteValue;
  red = readingData.redValue;
  val = readingData.swValue;

  // Motor control logic based on joystick input
  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, LOW);
  Serial.println("static");


  if (vrx < UP_THRESHOLD) {
    Serial.println("forward");

    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
    analogWrite(enA, speed);
    analogWrite(enB, speed);
  }

  if (vrx > DOWN_THRESHOLD) {
    Serial.println("down");

    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
    analogWrite(enA, speed);
    analogWrite(enB, speed);
  }

  if (vry > left) {
    Serial.println("left");

    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
    analogWrite(enA, speed);
    analogWrite(enB, speed);
  }

  if (vry < right) {
    Serial.println("right");
     digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
    analogWrite(enA, speed);
    analogWrite(enB, speed);

  }

  // Handle hand servo movement
  if (white == 1) {
    speed++;
    if (speed >=255)speed =255;
    Serial.print("speed now + : ");
    Serial.println(speed);
  }

  // Handle head servo movement
  if (red == 1) {
    speed--;
    if (speed <=100)speed =100;
    Serial.print("speed now - : ");
    Serial.println(speed);
 }
 }

void setup() {
  Serial.begin(115200);

  // Setup motor pins
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
 
  

  // Initialize ESP-NOW
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
 }

void loop(){
  // Empty loop, data processing handled in OnDataRecv
 
}
/*
void right_eye(){
  lcd.setCursor(5, 0);
  lcd.write(byte(1));
  lcd.setCursor(6, 0);
   lcd.write(byte(1));
   lcd.setCursor(5,1);
   lcd.write(byte(1));
   lcd.setCursor(6,1);
   lcd.write(byte(1));
}

void left_eye(){
  lcd.setCursor(9, 0);
  lcd.write(byte(1));
  lcd.setCursor(10, 0);
   lcd.write(byte(1));
   lcd.setCursor(9,1);
   lcd.write(byte(1));
   lcd.setCursor(10,1);
   lcd.write(byte(1));
}

void left_eyeS(){
  lcd.setCursor(9, 0);
  lcd.write(byte(2));
  lcd.setCursor(10, 0);
   lcd.write(byte(3));
   lcd.setCursor(9,1);
   lcd.write(byte(4));
   lcd.setCursor(10,1);
   lcd.write(byte(5));
}


/*
pending :
1. hand up and down
2. head up and down
3. test with lcd 

*/
