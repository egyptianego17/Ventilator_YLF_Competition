# BMP280

## You have to detect I<sub>2</sub>C address first
use this code to get it:
```
// --------------------------------------
// i2c_scanner
//
// Modified from https://playground.arduino.cc/Main/I2cScanner/
// --------------------------------------

#include <Wire.h>

// Set I2C bus to use: Wire, Wire1, etc.
#define WIRE Wire

void setup() {
  WIRE.begin();

  Serial.begin(9600);
  while (!Serial)
     delay(10);
  Serial.println("\nI2C Scanner");
}


void loop() {
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    WIRE.beginTransmission(address);
    error = WIRE.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print("Unknown error at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(5000);           // wait 5 seconds for next scan
}
```
![image](https://github.com/egyptianego17/Ventilator_YLF_Competition/assets/86708003/557b6030-f2c4-4d95-a2c4-aafbe755386a)
![image](https://github.com/egyptianego17/Ventilator_YLF_Competition/assets/86708003/36097b6b-3cb5-4ff2-91f0-61beaf853ab2)
![image](https://github.com/egyptianego17/Ventilator_YLF_Competition/assets/86708003/d134f043-706e-414e-9c73-ee0ad3f4bdc8)
![image](https://github.com/egyptianego17/Ventilator_YLF_Competition/assets/86708003/c820fe4b-49ab-493b-9625-a42271420efb)




## BMP280 Conninctions
![image](https://github.com/egyptianego17/Ventilator_YLF_Competition/assets/86708003/a1a696ed-a635-4f41-80c4-c9d01393bb0e)
