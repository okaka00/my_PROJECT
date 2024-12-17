#include <esp_now.h>
#include <WiFi.h>

#define rightJoyX     32
#define rightJoyY     35
#define rightJoySW    26
#define rightButtonA  2
#define rightButtonB  15

#define leftJoyX      34
#define leftJoyY      33
#define leftJoySW     25
#define leftButtonA   13
#define leftButtonB   12

#define LEDpin        23

int rightJoyXstate;
int rightJoyYstate;
int rightJoySWstate;
int rightButtonAstate;
int rightButtonBstate;
int leftJoyXstate;
int leftJoyYstate;
int leftJoySWstate;
int leftButtonAstate;
int leftButtonBstate;

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x0C, 0xB8, 0x15, 0xF2, 0xC1, 0x78};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  int rightJoyXvalue;
  int rightJoyYvalue;
  int rightJoySWvalue;
  int rightButtonAvalue;
  int rightButtonBvalue;
  int leftJoyXvalue;
  int leftJoyYvalue;
  int leftJoySWvalue;
  int leftButtonAvalue;
  int leftButtonBvalue;
} struct_message;

// Create a struct_message called myData
struct_message handControllerData;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
  pinMode(rightJoyX, INPUT);
  pinMode(rightJoyY, INPUT);
  pinMode(rightJoySW, INPUT);
  pinMode(rightButtonA, INPUT);
  pinMode(rightButtonB, INPUT);
  pinMode(leftJoyX, INPUT);
  pinMode(leftJoyY, INPUT);
  pinMode(leftJoySW, INPUT);
  pinMode(leftButtonA, INPUT);
  pinMode(leftButtonB, INPUT);
  pinMode(LEDpin, OUTPUT);

  digitalWrite(LEDpin, HIGH);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  // Set values to send
  rightJoyXstate = digitalRead(rightJoyX);
  handControllerData.rightJoyXvalue = rightJoyXstate;
  rightJoyYstate = digitalRead(rightJoyY);
  handControllerData.rightJoyYvalue = rightJoyYstate;
  rightJoySWstate = digitalRead(rightJoySW);
  handControllerData.rightJoySWvalue = rightJoySWstate;
  rightButtonAstate = digitalRead(rightButtonA);
  handControllerData.rightButtonAvalue = rightButtonAstate;
  rightButtonBstate = digitalRead(rightButtonB);
  handControllerData.rightButtonBvalue = rightButtonBstate;

  leftJoyXstate = digitalRead(leftJoyX);
  handControllerData.leftJoyXvalue = leftJoyXstate;
  leftJoyYstate = digitalRead(leftJoyY);
  handControllerData.leftJoyYvalue = leftJoyYstate;
  leftJoySWstate = digitalRead(leftJoySW);
  handControllerData.leftJoySWvalue = leftJoySWstate;
  leftButtonAstate = digitalRead(leftButtonA);
  handControllerData.leftButtonAvalue = leftButtonAstate;
  leftButtonBstate = digitalRead(leftButtonB);
  handControllerData.leftButtonBvalue = leftButtonBstate;

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &handControllerData, sizeof(handControllerData));

  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(50);
}
