#include "DHT.h"
#include "MAX30100.h"
#include <Wire.h>

#define DHTPIN 2    

#define DHTTYPE DHT22  

DHT dht(DHTPIN, DHTTYPE);
MAX30100 maxSensor;

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHT22 And MAX30100 test!"));
  while(!Serial);
  sensor.begin(pw1600, i50, sr100 );
  dht.begin();
}

void loop() {
  //  measurements delay
  delay(2000);

  maxSensor.readSensor();
  float h = dht.readHumidity();
  // temperature as Celsius
  float tc = dht.readTemperature();
  //temperature as Fahrenheit
  float tf = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(tc) || isnan(tf)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(tf, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(ct, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(tc);
  Serial.print(F("°C "));
  Serial.print(tf);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  Serial.print(F("Heart Rate: "));
  Serial.println(meanDiff(sensor.IR));
}


long meanDiff(int M) {
  #define LM_SIZE 15
  static int LM[LM_SIZE];      // LastMeasurements
  static byte index = 0;
  static long sum = 0;
  static byte count = 0;
  long avg = 0;

  // keep sum updated to improve speed.
  sum -= LM[index];
  LM[index] = M;
  sum += LM[index];
  index++;
  index = index % LM_SIZE;
  if (count < LM_SIZE) count++;

  avg = sum / count;
  return avg - M;
}