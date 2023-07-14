#ifndef INTERFACES_H
#define INTERFACES_H

#include "DHT.h"
#include "MAX30100.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <AccelStepper.h>
#include <Adafruit_BMP280.h>

#define DHTPIN              2    
#define DHTTYPE             DHT22  
#define LCD_ADDRESS         0x20
#define PIN1_ANALOG         A0
#define PIN2_ANALOG         A1
#define motorInterfaceType  1
#define DIR_PIN             2
#define STEP_PIN            3
/***** DO NOT Change These Macros Below *****/
#define DHT_HUMIDITY        0
#define DHT_TEMP_C          1
#define DHT_TEMP_F          2
#define DHT_HEAT_INDEX_C    3
#define DHT_HEAT_INDEX_F    4
/*******************************************/

AccelStepper myStepper(motorInterfaceType, STEP_PIN, DIR_PIN);
LiquidCrystal_I2C lcd(LCD_ADDRESS, 20, 4); 
DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP280  bmp; 
MAX30100 maxSensor;


#endif