#include "interfaces.h"

void setup() {
  // Initialize all modules
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
                  Adafruit_BMP280::STANDBY_MS_500);
}

void loop() {
   // Read analog voltage values from potentiometers
  int volume_voltage = getAnalogVoltage(PIN_VOLUME);
  int pressure_voltage = getAnalogVoltage(PIN_PRESSURE);
  
  if (!can_read_age_button && millis() - age_button_time >= 500) {
    can_read_age_button = true;
  }
  if (!can_read_start_button && millis() - start_button_time >= 500) {
    can_read_start_button = true;
  }
 
  if (!warn_user) {
    if (!ventilating) {
      check_age_setting();
    }
    LcdPrintUpdatedPotValues();
  }
 
  if (halt) {
    compression_state = 0;
    ventilating = false;
    StepperRunTillPosition(START_POS);
    release_time = millis();
  }
  halt = check_halt();
 
  if (warn_user) {
    flash_red();
  }
 
  if (ventilating) {
    uint16_t ms_per_breath = get_ms_per_breath();
    int16_t post_breath_delay = ms_per_breath - base_delays[age_state];
    if (post_breath_delay < 0) {
      post_breath_delay = 1000;
    }
        if (time_to_squeeze && !compression_state) {
      compression_state = 1;
      uint16_t des_vol = nom_vals[VOL][age_state];
      des_vol += val_inc[VOL][age_state] * pot_vals[VOL];
      uint16_t dest = vol_to_ang(des_vol);
      if (age_state == 0) {
 
        dest = map(dest, 193, 208, 180, 250);
      }
      StepperRunTillPosition(dest);

      squeeze_time = millis();
    } else if (time_to_release && compression_state) {
 
      if (current_sum >= predict_current() * 1.2 && age_state == 0) {
        halt = true;
        green_led(false);
        warn_user = true;
 
      } else {
        compression_state = 0;
        StepperRunTillPosition(START_POS);
        release_time = millis();
      }
      current_sum = 0;
    }
    time_to_squeeze = millis() - release_time > post_breath_delay;
    time_to_release = millis() - squeeze_time > base_delays[age_state];
  }


 
  // Convert the voltage values to tidal volume, PIP, and PEEP pressures
  tidal_volume = map(volume_voltage, 0, 1023, 0, 1000); // in mL
  PIP_pressure = map(pressure_voltage, 0, 1023, 0, 50); // in cmH2O
  PEEP_pressure = map(pressure_voltage, 0, 1023, 0, 20); // in cmH2O
  
  // Read sensor values
  float* dht_values = ReadDHT_Values(); // DHT22 sensor
  long max_sensor_value = ReadMaxSensor(); // MAX30100 sensor
  float temperature_c = BMP_readTemperature_c(); // BMP280 sensor
  float pressure_hPa = BMP_readPressure_hPa(); // BMP280 sensor
  float altitude_m = BMP_readAltitude_m(); // BMP280 sensor
  LCD_PrintValues(tidal_volume,PIP_pressure,dht_values,max_sensor_value);
  // Delay for a short time to allow the stepper motor to move
  delay(10);
}

