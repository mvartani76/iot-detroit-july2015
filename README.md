# arduino-iot-test-july2015
Sample server and client code for demonstrating simple data logging from sensors

Place Arduino OneWire and dtc Library Folders in <your-path-to-Arduino-Directory>\libraries directory

# Arduino Twitter Code

The Arduino Twitter code is a collection of an Arduino sketch, ArduinoSensorCode_Twitter\ArduinoSensorCode_Twitter.ino, and php code/libraries /php/TwitterTest/. The Arduino code is very similar to the code used to read the sensor values off the Arduino and send to the personal cloud via php (php/SensorRead_MySQL & php/SensorRead_MySQL) but now we send the HTTP GET request to a different php file.

The TwitterOAuth libraries are taken from the following location:
https://github.com/abraham/twitteroauth with further documentation located here: https://twitteroauth.com/
