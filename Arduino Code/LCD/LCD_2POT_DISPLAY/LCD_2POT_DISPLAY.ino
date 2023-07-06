#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define LCD_ADDRESS   0x20
#define PIN1_ANALOG   A0
#define PIN2_ANALOG   A1
LiquidCrystal_I2C lcd(LCD_ADDRESS, 20, 4); // set the LCD address to 0x27 for a 20x4 display

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

}

void loop()
{
  // read the input on analog pin A0:
  int analogValue = analogRead(PIN1_ANALOG);
  // Rescale the analog value to potentiometer's voltage (0V to 5V):
  float voltage1 = ( analogValue/ 1023.0);
  Serial.println(voltage1);

  // read the input on analog pin A1:
  int analogValue2 = analogRead(PIN2_ANALOG);
  // Rescale the analog value to potentiometer's voltage (0V to 5V):
  float voltage2 = ( analogValue2  / 1023.0);
  Serial.println(voltage2);

  lcd.setCursor(0, 0);
  lcd.print("V1:");
  lcd.setCursor(0, 1);
  lcd.print(voltage1);
  lcd.setCursor(0, 2);
  lcd.print("V2:");
  lcd.setCursor(0, 3);
  lcd.print(voltage2);

  delay(500);
}
