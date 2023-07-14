#include "interfaces.h"


void setup() {

 All_Modules_Init();

}

void loop() {
  //  measurements delay
  delay(2000);
     
  int analogVoltage1 = getAnalogVoltage(PIN1_ANALOG);  
  Serial.println(analogVoltage1);

  int analogVoltage2 = getAnalogVoltage(PIN2_ANALOG);  
  Serial.println(analogVoltage2);

  LCD_PrintAnalogVoltages(analogVoltage1,analogVoltage2);

  long HeartRate = ReadMaxSensor();

  float* DHT_Values = ReadDHT_Values();
  SerialPrintDHT_Values(DHT_Values);

  I2C_ScanDevices();

  StepperRunTillPosition();

  BMP_readPressure_hPa();//etc..

}

