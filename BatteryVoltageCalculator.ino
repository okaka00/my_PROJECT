#ifndef BATTERY_VOLTAGE_CALCULATOR_H
#define BATTERY_VOLTAGE_CALCULATOR_H
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

      int sensorValue;
      float voltage;
      float info;


      float VoltageBattery (int b){
        sensorValue = analogRead(b);
        voltage = sensorValue * (12.6/3572.204);  // read analog value 
        return voltage; 
      }
      
      if(buttonPressed==true){
      switch(selection){
        case 1:
        info = VoltageBattery(batt1);
        break;

        case 2:
        info = VoltageBattery(batt2);
        break;

        case 3:
        info = VolategBattery(batt3);
        break;

        case 4:
        info = VoltageBattery(batt4);
        break;

        default:
        lcd.print("No Battery Selected");
      }
      } else {
        lcd.print("No Battery Selected");
      }



#endif
