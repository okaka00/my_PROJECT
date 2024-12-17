
const int e18_sensor = 27;
const int led = 2;

void setup() {
  Serial.begin(115200);
pinMode (e18_sensor, INPUT);
pinMode (led, OUTPUT);
digitalWrite(led, HIGH);
}

void loop() {
  int state = analogRead(e18_sensor);
  //int digital =digitalRead(e18_sesor);
  Serial.println("sensor value analog : ");
  Serial.println(state);
  //Serial.println("sensor value digital : ");
//  Serial.println(digital);
 // digitalWrite(led, HIGH);
  //(200);

}
