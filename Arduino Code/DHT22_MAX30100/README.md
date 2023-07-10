Ventilator Device Prototype
This project is a prototype of a ventilator device that includes the DHT22 and MAX30100 sensors.
The DHT22 sensor measures temperature and humidity, 
while the MAX30100 sensor measures heart rate and blood oxygen saturation.

Hardware Requirements
STM32 microcontroller
DHT22 sensor
MAX30100 sensor

Software Requirements
Arduino IDE
DHT library
MAX30100 library

Setup
Install the DHT and MAX30100 libraries in the Arduino IDE.
Copy and paste the code in the Arduino IDE.
Upload the code to the Arduino Board.

Code Explanation
DHT22 Sensor
The DHT22 sensor is a digital temperature and humidity sensor that communicates with the microcontroller 
over a single-wire interface.
The following functions are used to interface with the DHT22 sensor:

dht.begin(): This function initializes the DHT22 sensor and sets up the communication with the microcontroller.
dht.readTemperature(): This function reads the temperature data from the DHT22 sensor and returns the value in Celsius.
dht.readHumidity(): This function reads the humidity data from the DHT22 sensor and returns the value as a percentage.

MAX30100 Sensor
The MAX30100 sensor is a pulse oximeter and heart-rate sensor that communicates with the microcontroller 
over an I2C interface. 
The following functions are used to interface with the MAX30100 sensor:

maxSensor.begin(pw1600, i50, sr100): This function initializes the MAX30100 sensor and sets up the communication with the microcontroller.
maxSensor.readSensor(): This function reads the data from the MAX30100 sensor and stores it in the sensor.IR buffer.
meanDiff(sensor.IR): This function calculates the heart rate from the MAX30100 sensor data.
	It uses a moving average filter to smooth out the data and calculates the mean difference between consecutive samples.
maxSensor.getSpO2(): This function calculates the blood oxygen saturation based on the data in the buffer and returns the value as a percentage.
Conclusion
This prototype demonstrates how the DHT22 and MAX30100 sensors can be used in a ventilator device to measure 
temperature, humidity, heart rate, and blood oxygen saturation.