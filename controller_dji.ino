#include "WiFi.h"
#include "esp_now.h"
#include <ezButton.h>



#define VRX 35
#define VRY 32
#define SW 17
#define redB 2
#define whiteB 15

ezButton button(SW);

int stateRed;
int stateWhite;
int stateSwitch;
int valueVRX=0;
int valueVRY=0;
float mag;

//address of the receiver esp32
uint8_t ReceiverAddress[] = {0x08, 0xD1, 0xF9, 0xE6, 0xBD, 0x18};
//08:D1:F9:E6:BD:18(dji)
//08:D1:F9:3B:0B:A8(normal)

//here all the variable that will be send to esp
typedef struct struct_message {
  int redValue;
  int whiteValue;
  int valueX;
  int valueY;
  int swValue;
}struct_message;

struct_message senderData;

esp_now_peer_info_t peerInfo;


// function that will indicate the message was sent to the receiver esp
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status){
  Serial.print("\r\nLast Packaet Send Status: \t"); 
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? " DELIVERY SUCCESS" : "Delivery Fail");
 //delay(1000);
}

void setup() {
 Serial.begin(115200);
 
 pinMode(redB, INPUT);
 pinMode(whiteB, INPUT);
 pinMode(VRX, INPUT);
 pinMode(VRY, INPUT);

button.setDebounceTime(10); // set debounce time to 50 milliseconds
 WiFi.mode(WIFI_STA);

 if(esp_now_init() != ESP_OK){
  Serial.println("Error initializing ESP_NOW");
  return;
 }
 esp_now_register_send_cb(OnDataSent);

  // Register peer
  memcpy(peerInfo.peer_addr, ReceiverAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

}

void loop() {
  button.loop(); // MUST call the loop() function first



  stateSwitch = button.getState();
  senderData.swValue = stateSwitch;
//stateRed is the value from the button, will be pass to the redValue by using senderData struct message
  stateRed = digitalRead(redB);
  senderData.redValue = stateRed;

  stateWhite = digitalRead(whiteB);
  senderData.whiteValue = stateWhite;

  valueVRX = analogRead(VRX);
  senderData.valueX = valueVRX;
  valueVRY = analogRead(VRY);
  senderData.valueY = valueVRY;

  Serial.print("\nvrx : ");
  Serial.println(valueVRX);
    Serial.print("\nvry : ");
  Serial.println(valueVRY);
Serial.print("\nswitch: ");
  Serial.println(stateSwitch);


 
 //this function is the one sending data to the receiver esp.
  esp_err_t result = esp_now_send(ReceiverAddress, (uint8_t *) &senderData, sizeof(senderData));

  if(result == ESP_OK){
    Serial.println("Sent with Success");
   //delay(1000);
  }
  else {
    Serial.println("Error sending data");
    //delay(1000);
  }
  
}
