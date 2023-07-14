#include "interfaces.h"

void All_Modules_Init(){
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  while(!Serial);
  Wire.begin();
  maxSensor.begin(pw1600, i50, sr100 );
  dht.begin();
  // set the maximum speed, acceleration factor,
	// initial speed and the target position
	myStepper.setMaxSpeed(1000);
	myStepper.setAcceleration(50);
	myStepper.setSpeed(200);
	myStepper.moveTo(200);
  
  if  (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor,  check wiring!"));
    while (1);
  }

  /* Default settings from datasheet.  */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500);  /* Standby time. */
}
int getAnalogVoltage(int analogPin){
  int analogValue = analogRead(PIN1_ANALOG);// read the input on analog pin A0:
  float voltage1 = ( analogValue/ 1023.0); // Rescale the analog value to potentiometer's voltage (0V to 5V):
}
void LCD_PrintAnalogVoltages(int v1,int v2){

  lcd.setCursor(0, 0);
  lcd.print("V1:");
  lcd.setCursor(0, 1);
  lcd.print(v1);
  lcd.setCursor(0, 2);
  lcd.print("V2:");
  lcd.setCursor(0, 3);
  lcd.print(v2);

}
long ReadMaxSensor() {
 
  maxSensor.readSensor();

  int IR_Val = maxSensor.IR;

  #define LM_SIZE 15
  static int LM[LM_SIZE];      // LastMeasurements
  static byte index = 0;
  static long sum = 0;
  static byte count = 0;
  long avg = 0;

  // keep sum updated to improve speed.
  sum -= LM[index];
  LM[index] = IR_Val;
  sum += LM[index];
  index++;
  index = index % LM_SIZE;
  if (count < LM_SIZE) count++;

  avg = sum / count;
  return avg - IR_Val;
}
float* ReadDHT_Values(){
  float values[5] = {0};

  values[DHT_HUMIDITY] = dht.readHumidity();
  // temperature as Celsius
  values[DHT_TEMP_C] = dht.readTemperature();
  //temperature as Fahrenheit
  values[DHT_TEMP_F] = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(values[DHT_HUMIDITY]) || isnan(values[DHT_TEMP_C]) || isnan(values[DHT_TEMP_F])) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  values[DHT_HEAT_INDEX_F] = dht.computeHeatIndex(values[DHT_TEMP_F], values[DHT_HUMIDITY]);
  // Compute heat index in Celsius (isFahreheit = false)
  values[DHT_HEAT_INDEX_C] = dht.computeHeatIndex(values[DHT_TEMP_C], values[DHT_HUMIDITY], false);


  return values;
}
void SerialPrintDHT_Values(float* DHT){
    
  Serial.print(F("Humidity: "));
  Serial.print(DHT[DHT_HUMIDITY]);
  Serial.print(F("%  Temperature: "));
  Serial.print(DHT[DHT_TEMP_C]);
  Serial.print(F("°C "));
  Serial.print(DHT[DHT_TEMP_F]);
  Serial.print(F("°F  Heat index: "));
  Serial.print(DHT[DHT_HEAT_INDEX_C]);
  Serial.print(F("°C "));
  Serial.print(DHT[DHT_HEAT_INDEX_F]);
  Serial.println(F("°F"));

  
}
void I2C_ScanDevices(){
  int nDevices = 0;

  Serial.println("Scanning...");

  for (byte address = 1; address < 127; ++address) {
    // The i2c_scanner uses the return value of
    // the Wire.endTransmission to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address, HEX);
      Serial.println("  !");

      ++nDevices;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  } else {
    Serial.println("done\n");
  }

}
void StepperRunTillPosition(){

  // Change direction once the motor reaches target position
	if (myStepper.distanceToGo() == 0) 
		myStepper.moveTo(-myStepper.currentPosition());

	// Move the motor one step
	myStepper.run();
}
float BMP_readTemperature_c(){
  return bmp.readTemperature();
}
float BMP_readPressure_hPa(){
  return bmp.readPressure()/100;
}
float BMP_readAltitude_m(){
  return bmp.readAltitude(1019.66);
}
float BMP_readTemperature_f(){
  return bmp.readTemperature()*9/5 + 32;
}
float BMP_readPressure_hg(){
  return bmp.readPressure()/3386.39;
}
float BMP_readAltitude_ft(){
  return bmp.readAltitude(1019.66)*3.28084;
}

