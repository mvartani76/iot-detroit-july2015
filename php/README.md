# php Sample Code
Sample php code for receiving sensor data through HTTP GET requests and then either logging in MySQL database or tweeting via Twitter API

**SensorRead_MySQL** - This code receives the HTTP GET reqeusts and logs them into a user defined MySQL database. It consists of three files: db_connection.php, addsensordata.php, and displaysensordata.php


**TwitterTest** - This code receives the HTTP GET reqeusts and then uses a POST request to the twitter API to tweet the sensor data.

The TwitterOAuth libraries are taken from the following location:
https://github.com/abraham/twitteroauth with further documentation located here: https://twitteroauth.com/

