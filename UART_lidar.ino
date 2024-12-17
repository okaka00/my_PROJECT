#include <HardwareSerial.h> // Reference the ESP32 built-in serial port library
HardwareSerial lidarSerial(2); // Using serial port 2
#define RXD2 16
#define TXD2 17

void setup() {
  Serial.begin(115200); // Initializing serial port
  lidarSerial.begin(115200, SERIAL_8N1, RXD2, TXD2); // Initializing serial port
}

void loop() {
  uint8_t buf[9] = {0}; // An array that holds data
  if (lidarSerial.available() > 0) {
    lidarSerial.readBytes(buf, 9); // Read 9 bytes of data
    if( buf[0] == 0x59 && buf[1] == 0x59)
    {
      uint16_t distance = buf[2] + buf[3] * 256;
      Serial.println("Distance: ");
      Serial.println(distance);
    }
  }
  //delay(10); 
}