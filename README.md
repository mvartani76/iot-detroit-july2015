# IoT-Detroit-July2015 Workshop Source Code
Collection of code for IoT-Detroit Meetup Workshop July 2015

This repository has three sub-directories: Arduino, RaspberryPi, and php.

**Arduino** - This subdirectory contains several samples of code written for the Arduino UNO. The code reads values from external sensors and sends them to either a user created MySQL database or tweets them to a user created twitter account. There are separate Arduino sketches for each including variants for ethernet and wifi connectivity.

**RaspberryPi** - This subdirectory contains several samples of python code written for the Raspberry Pi. Similar to the collection of Arduino code, this code reads values from external sensors and sends them to either a user created MySQL database or tweets them to a user created twitter account. There are no distinctions between ethernet and WiFi variants as the connectivity control is in a different file and not in the source code as it is for the Arduino UNO.

**php** - This subdirectory contains the code (written in php obviously) that actually connects to the MySQL database and/or Twitter API to post the data read from the sensors.
