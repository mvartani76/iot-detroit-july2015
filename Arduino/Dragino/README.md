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
	<li>Connect to Yun Shield -- At the first boot of Yun Shield, it will auto generate an unsecure WiFi network call Dragino2-xxxxxx. Use your laptop to connect to this WiFi network. The laptop will get an IP 192.168.240.xxx and the Yun Shield has the default IP 192.168.240.1</li>
	<li>Set Up Yun Shield to access Internet - After joining the network, the settings homepage will ask for password (the default password is dragino). After login,the GUI will show the WIFI / ETH interface status.</li>
	<li>Click the Configure button and now user can configure Yun Shield to access internet via your WiFi router.</li>
	<li> Add Dragino Yun Shield Board Configurations - grab the boards.txt file from https://github.com/dragino/modules/blob/master/hardware/YunShield/sketchbook/hardware/YunShield/avr/boards.txt and insert the code below into the <yourpathtoArduino>/Arduino/hardware/arduino/avr/boards.txt file.
		<blockquote>unoyun.name=Arduino Uno -- Dragino Yún</br></br>
 unoyun.upload.via_ssh=true</br></br>

 unoyun.vid.0=0x2341</br>
 unoyun.pid.0=0x0043</br>
 unoyun.vid.1=0x2341</br>
 unoyun.pid.1=0x0001</br>
 unoyun.upload.tool=avrdude</br>
 unoyun.upload.protocol=arduino</br>
 unoyun.upload.maximum_size=32256</br>
 unoyun.upload.maximum_data_size=2048</br>
 unoyun.upload.speed=57600</br>
 unoyun.upload.disable_flushing=true</br>
 unoyun.upload.use_1200bps_touch=true</br>
 unoyun.upload.wait_for_upload_port=true</br></br>

 unoyun.bootloader.tool=avrdude</br>
 unoyun.bootloader.low_fuses=0xff</br>
 unoyun.bootloader.high_fuses=0xde</br>
 unoyun.bootloader.extended_fuses=0x05</br>
 unoyun.bootloader.file=optiboot/optiboot_atmega328.hex</br>
 unoyun.bootloader.unlock_bits=0x3F</br>
 unoyun.bootloader.lock_bits=0x0F</br></br>

 unoyun.build.mcu=atmega328p</br>
 unoyun.build.f_cpu=16000000L</br>
 unoyun.build.board=AVR_YUN</br>
 unoyun.build.core=arduino</br>
 unoyun.build.variant=standard</blockquote></li>.
	<li>Detect Yun Shield -- Assume your laptop and Yun Shield are in the same network. The Yun Shield will broadcast data in this network and Arduino IDE will receive this data and show the Yun Shield in Tools>Port.</li>
	<li>Add/replace libraries -- Compared to the WiFi/Ethernet equivalent code, we need to make a few changes to the code to get it to work with the Dragino YUN SHIELD. First we need to replace the WiFi/Ethernet library includes with the Yun Client and Yun Server libraries. Second, replace the WiFi/Ethernet client declaration with a YunClient declaration. And third, replace the serial calls with console calls.
	<img src="../Arduino-Images/dragino-change-clients.png" alt="Change client declaration to YunClient"></li>
</ol>
