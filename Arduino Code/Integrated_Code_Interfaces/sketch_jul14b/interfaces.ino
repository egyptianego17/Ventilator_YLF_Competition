#include "interfaces.h"

int getAnalogVoltage(int analogPin){
  int analogValue = analogRead(analogPin);// read the input on analog pin A0 or A1:
  float voltage1 = ( analogValue/ 1023.0); // Rescale the analog value to potentiometer's voltage (0V to 5V):
}
void LCD_PrintValues(int vol,int pip,float* DHT,long max_sensor_value ){

  lcd.setCursor(0, 0);
  lcd.print("VOL:");
  lcd.setCursor(6, 0);
  lcd.print(vol);
  lcd.setCursor(10, 0);
  lcd.print("PIP:");
  lcd.setCursor(16, 0);
  lcd.print(pip);

  lcd.setCursor(0, 1);
  lcd.print("HUM:");
  lcd.setCursor(5, 1);
  lcd.print(DHT[DHT_HUMIDITY]);
  lcd.setCursor(8, 1);
  lcd.print("Temp:");
  lcd.setCursor(16, 1);
  lcd.print(DHT[DHT_TEMP_C]);

    lcd.setCursor(0, 2);
  lcd.print("Heart Bitrate:");
  lcd.setCursor(15, 2);
  lcd.print(max_sensor_value);
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
void StepperRunTillPosition(uint16_t dest){
    myStepper.moveTo(dest);
    while(myStepper.distanceToGo() != 0);// poling
     // Change direction once the motor reaches target position

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
//////////////////////////////////////////////////////////////////////////////////
  
void check_age_setting() {
  if (!digitalRead(P_SETTING_BUTTON) && can_read_age_button) {
    age_button_time = millis();
    can_read_age_button = false;
    age_state = (age_state + 1) % 3;
    switch(age_state){
      case  0 :
      lcd.println("age state : Adult ");
      break;
      case  1 :
      lcd.println("age state : Child ");
      break;
      case  2 :
      lcd.println("age state : Infant ");
      break;
    }
  }
}
 
int mapPotValues(uint16_t unmapped_pot_val, int8_t pot_index) {
  return map(unmapped_pot_val, 0, 1024, 5, -5);
}
  
void LcdPrintUpdatedPotValues() {
///////////////////////////////////////////////
int v1 = getAnalogVoltage(PIN_VOLUME);
int v2 = getAnalogVoltage(PIN_PRESSURE);
 lcd.setCursor(0, 1);
  lcd.print("HUM:");
  lcd.setCursor(5, 1);
  lcd.print(v1);
  lcd.setCursor(8, 1);
  lcd.print("Temp:");
  lcd.setCursor(16, 1);
  lcd.print(v2);
}

 
void check_start_stop() {
  if (!digitalRead(P_START_BUTTON) && can_read_start_button) {
    if (warn_user) {
      red_led(true);
      warn_user = false;
      lcd.init();
    } else {
      start_button_time = millis();
      can_read_start_button = false;
      ventilating = !ventilating;
      red_led(!ventilating);
      green_led(ventilating);
    }
  }
}
 
bool check_halt() {
  if (ventilating && warn_user) {
    return true;
  }
  bool was_ventilating = ventilating;
  check_start_stop();
  if (was_ventilating && !ventilating) {
    return true;
  }
  return false;
}
  
uint16_t get_ms_per_breath() {
  uint8_t breath_per_min = nom_vals[RATE][age_state] + val_inc[RATE][age_state] * pot_vals[RATE];
  return round(1000 / (breath_per_min / 60.0));
}
 
uint16_t vol_to_ang(uint16_t vol) {
  return 4.89427e-7 * pow(vol, 3) - 8.40105e-4 * pow(vol, 2) + 0.64294 * vol + 28.072327;
}
 
void red_led(bool on) {
 
  analogWrite(P_RED_LED, on ? 5 : 0);
}
 
void green_led(bool on) {
  digitalWrite(P_GREEN_LED, on ? HIGH : LOW);
}

void flash_red() {
  if ((millis() - red_led_flash) > 200) {
    red_led(!red_led_flash_on);
    red_led_flash_on = !red_led_flash_on;
    red_led_flash = millis();
  }
}
 
double predict_current() {
 
  uint16_t v = nom_vals[0][age_state] + val_inc[0][age_state] * pot_vals[0];
  uint8_t p = nom_vals[1][age_state] + val_inc[1][age_state] * pot_vals[1];
  return -1.041041e3 + 2.35386 * v + 2.316309e-3 * pow(v, 2) - 3.887507e1 * p + 7.7198644 * pow(p, 2) - 4.2099326e-2 * v * p;
}
 
void update_current() {
 
  uint16_t potentiometer_raw = analogRead(P_CURRENT);
  double voltage_raw = (5.0 / 1023.0) * analogRead(VIN);
  voltage = voltage_raw - QOV + 0.012;
  double current = voltage / sensitivity[MODEL] * -1;
  current_sum += current;
}
