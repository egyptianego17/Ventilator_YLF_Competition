# Ventilator Device Prototype(Test for the DHT22 and MAX30100)

<h2>This project is a prototype of a ventilator device that includes the DHT22 and MAX30100 sensors.</h2>
<p>	
The DHT22 sensor measures temperature and humidity, 
while the MAX30100 sensor measures heart rate and blood oxygen saturation.
</p>
<h2>Hardware Requirements</h2>
<ol>
<li>STM32 microcontroller</li>
<li>DHT22 sensor</li>
<li>MAX30100 sensor</li>
</ol>
<h2>Software Requirements</h2>
<ol>
<li>Arduino IDE</li>
<li>DHT library</li>
<li>MAX30100 library</li>
</ol>
<h2>Setup</h2>
<ul>
<li>Install the DHT and MAX30100 libraries in the Arduino IDE.</li>

<li>Copy and paste the code in the Arduino IDE.</li>

<li>Upload the code to the Arduino Board.</li>
</ul>
<h2>Code Explanation</h2>
<h3>DHT22 Sensor</h3>
The DHT22 sensor is a digital temperature and humidity sensor that communicates with the microcontroller 
over a single-wire interface.

The following functions are used to interface with the DHT22 sensor:

<b>dht.begin():</b> This function initializes the DHT22 sensor and sets up the communication with the microcontroller.

<b>dht.readTemperature():</b> This function reads the temperature data from the DHT22 sensor and returns the value in Celsius.

<b>dht.readHumidity():</b> This function reads the humidity data from the DHT22 sensor and returns the value as a percentage.

<h3>MAX30100 Sensor</h3>

The MAX30100 sensor is a pulse oximeter and heart-rate sensor that communicates with the microcontroller 

over an I2C interface. 

The following functions are used to interface with the MAX30100 sensor:

<b>maxSensor.begin(pw1600, i50, sr100):</b> This function initializes the MAX30100 sensor and sets up the communication with the microcontroller.

<b>maxSensor.readSensor():</b> This function reads the data from the MAX30100 sensor and stores it in the sensor.IR buffer.

<b>meanDiff(sensor.IR):</b> This function calculates the heart rate from the MAX30100 sensor data.
	It uses a moving average filter to smooth out the data and calculates the mean difference between consecutive samples.
	
<b>maxSensor.getSpO2():</b> This function calculates the blood oxygen saturation based on the data in the buffer and returns the value as a percentage.

<h2>Conclusion</h2>

This prototype demonstrates how the DHT22 and MAX30100 sensors can be used in a ventilator device to measure 

temperature, humidity, heart rate, and blood oxygen saturation.
