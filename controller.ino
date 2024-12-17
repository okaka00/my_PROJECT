#include "WiFi.h"
#include "esp_now.h"

//#include <ezButton.h>

#define VRX 35
#define VRY 32
#define SW 17
#define redB 2
#define whiteB 15
//ezButton button(SW);

int stateRed;
int stateWhite;
int stateSwitch;
int valueVRX=0;
int valueVRY=0;

//address of the receiver esp32
uint8_t ReceiverAddress[] = {0xfc, 0xe8, 0xc0, 0x7d, 0xc7, 0xf0};// FC:E8:C0:7D:C7:F0

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
      //remove the delay to reduce the delay for the data to send
  //delay(1000);
}

void setup() {
 Serial.begin(115200);
 pinMode(redB, INPUT);
 pinMode(whiteB, INPUT);
 pinMode(VRX, INPUT);
 pinMode(VRY, INPUT);
 pinMode(SW, INPUT_PULLUP); // Use pull-up resistor


//button.setDebounceTime(10); // set debounce time to 50 milliseconds
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
  //button.loop(); // MUST call the loop() function first

  stateSwitch = digitalRead(SW);
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
  Serial.print("\nRed Button value  : ");
  Serial.println(stateRed);
  Serial.print("\nWhite Button Value : ");
  Serial.println(stateWhite);
  Serial.print("\nvrx : ");
  Serial.println(valueVRX);
  Serial.print("\nvry : ");
  Serial.println(valueVRY);
  Serial.print("\nswitch: ");
  Serial.println(stateSwitch);
  //delay(1000);


 //this function is the one sending data to the receiver esp.
  esp_err_t result = esp_now_send(ReceiverAddress, (uint8_t *) &senderData, sizeof(senderData));

  if(result == ESP_OK){
    Serial.println("Sent with Success");
    //remove the delay to reduce the delay for the data to send
  //delay(1000);
  }
  else {
    Serial.println("Error sending data");
   // delay(1000);
  }
  
}
