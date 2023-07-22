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
#define PIN_VOLUME          A0
#define PIN_PRESSURE        A1

// PIN connections for stepper motor
#define STEPPER_MOTOR_PIN_1 8
#define STEPPER_MOTOR_PIN_2 9
#define STEPPER_MOTOR_PIN_3 10
#define STEPPER_MOTOR_PIN_4 11
///////////////////////////////////////////
#define P_START_BUTTON      5
#define P_RED_LED           6
#define P_GREEN_LED         7
#define P_SETTING_BUTTON    8
#define START_POS           200
///////////////////////////////////////////
#define VOL                 111
#define RATE                54
#define P_CURRENT           54
#define VIN                 54
#define QOV                 54
#define MODEL               54
// Define the number of steps per revolution
const int STEPS_PER_REVOLUTION = 2048;

// Define the tidal volume, PIP, and PEEP pressures
int tidal_volume = 0;
int PIP_pressure = 0;
int PEEP_pressure = 0;

// Define the target pressure levels
int target_PIP_pressure = 20; // in cmH2O
int target_PEEP_pressure = 5; // in cmH2O
 
bool ventilating = false;
bool time_to_squeeze = true;
bool time_to_release = true;
long squeeze_time = -100;
long release_time = -100;
bool compression_state = 0;
bool halt = false;
bool warn_user = false;
bool can_read_age_button = true;
long age_button_time = -100;
bool can_read_start_button = true;
long start_button_time = -100;
uint8_t age_state = 0;
long red_led_flash = 0;
bool red_led_flash_on = false;
 
double sensitivity[] = { 0.185, 0.100, 0.066 };
double voltage;
double current_sum = 0;

const uint16_t nom_vals[3][3] = { { 500, 300, 25 }, { 5, 5, 5 }, { 12, 25, 50 } };
const uint8_t val_inc[3][3] = { { 10, 5, 1 }, { 1, 1, 1 }, { 1, 1, 2 } }; 
const uint16_t base_delays[3] = { 950, 550, 200 };
int8_t pot_vals[3] = { 0, 0, 0 };

// Create a stepper object
AccelStepper stepper(AccelStepper::FULL4WIRE, STEPPER_MOTOR_PIN_1, STEPPER_MOTOR_PIN_3, STEPPER_MOTOR_PIN_2, STEPPER_MOTOR_PIN_4);

AccelStepper myStepper(motorInterfaceType, STEP_PIN, DIR_PIN);
LiquidCrystal_I2C lcd(LCD_ADDRESS, 20, 4); 
DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP280  bmp; 
MAX30100 maxSensor;


#endif