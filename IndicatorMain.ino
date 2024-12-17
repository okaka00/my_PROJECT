#include <LiquidCrystal_I2C.h>
#include <Arduino.h> 

#define Button_Pin 27

const int batt1 = 33;
const int batt2 = 32;
const int batt3 = 35;
const int batt4 = 34;
const int p = 13;
float info = 0.0;
//const int pushButton = 15;
bool buttonPressed = false;//off
 // Number of samples to take
//int sensorValue;
int potentionMeter=0;
LiquidCrystal_I2C lcd (0x27, 16,2);


 void setup () 
        {

        Serial.begin(115200);
        lcd.init();
        lcd.backlight();
        lcd.print("WOOF WOOF");
        delay(2000);
        lcd.clear();
        
          }
void loop () 
    { 
          potentionMeter = analogRead(p);
          int selection = map(potentionMeter, 0, 4095, 1, 4);
          lcd.setCursor(0,0);
          lcd.print("BATTERY : ");
          lcd.setCursor(10,0);
          lcd.print(selection);
          lcd.setCursor(0,1);


           switch(selection){
        case 1:
        info = VoltageBattery(batt1);
        break;

        case 2:
        info = VoltageBattery(batt2);
        break;

        case 3:
        info = VoltageBattery(batt3);
        break;

        case 4:
        info = VoltageBattery(batt4);
        break;

        default:
        lcd.print("No Battery Selected");
      }


          lcd.print(info);
         delay(200);
         lcd.clear();

    }

     float VoltageBattery (int b){
       int sensorValue = analogRead(b);
        float voltage = sensorValue * (12.6/3572.204);  // read analog value 
        return voltage; 
      }
 
