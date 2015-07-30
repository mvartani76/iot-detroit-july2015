# Arduino Sample Code
Sample code for demonstrating simple data logging from DS18B20 Temperature Sensor and Analog photoresistor

Arduino UNO has both digital and analog input pins so we can just connect the sensors appropriate without any additional ADCs.

**Libraries** - This directory contains the necessary libraries for the Xively platform and the sensors

Place Arduino OneWire and dtc Library Folders in <your-path-to-Arduino-Directory>\libraries directory

**ArduinoSensorCodeDBEthnt/WiFi** - These two Arduino sketches send HTTP GET requests to a user defined php file that has previously connected to an MySQL database.

**ArduinoSensorCode_TwitterEthnt/WiFi** - These two Arduino sketches send HTTP GET requests to a user defined php file that uses the Twitter API to tweet the sensor values to the user defined Twitter account. Note that this code is exactly the same as the code above with the exception as to the file location where the HTTP GET request is sent.

The TwitterOAuth libraries are taken from the following location:
https://github.com/abraham/twitteroauth with further documentation located here: https://twitteroauth.com/

**Arduino_Xively_Ethnt/WiFi_App** - These two Arduino sketches send the sensor reading data to the Xively Platform.

# Tools / Software Used

For these examples, I was using an Arduino UNO R3 with ether a WiFi Shield or Ethernet shield with Arduino IDE 1.6.5 from https://www.arduino.cc/en/main/software running on a Windows 7 64 bit Dell Inspiron
