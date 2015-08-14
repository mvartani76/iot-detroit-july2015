# Arduino Sample Code using Dragino Yun Shield
Sample code for demonstrating simple data logging from DS18B20 Temperature Sensor and Analog photoresistor and then either storing in MySQL database or tweeting the values using the Twitter API.

The difference with this code is that it uses the Dragino Yun Shield...

## Dragino Yun Shield </br>
<p align="center">
	<img src="../Arduino-Images/dragino-yun-shield.png" alt="Dragino Yun Shield">
</p>


## How do I configure the Dragino Yun Shield and the Arduino UNO Code to work with the Yun Shield?
<ol>
	<li>Jumper pins 1/2 (closest to the reset button) of the ICSP header on the Arduino UNO board
		<img src="../Arduino-Images/arduinoUNOR3-header.png" alt="Arduino UNO R3 showing ICSP header"></li>
	<li>Connect the Dragino Yun Shield to the Arduino UNO</li>
	<li>Power the boards using a DC power supply ~+7v-+15v</li>
	<li>At the first boot of Yun Shield, it will auto generate an unsecure WiFi network call Dragino2-xxxxxx. Use your laptop to connect to this WiFi network. The laptop will get an IP 192.168.240.xxx and the Yun Shield has the default IP 192.168.240.1</li>
</ol>