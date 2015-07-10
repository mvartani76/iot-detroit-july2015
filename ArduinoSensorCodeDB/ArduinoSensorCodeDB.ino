#include <SPI.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#include <OneWire.h>
#include <DallasTemperature.h>

#ifndef __CREDENTIALS_H__
#define __CREDENTIALS_H__
char pass[] = "bakedpotato99"; //password Wi-Fi
char ssid[] = "vartaniannet"; //name Wi-Fi
int status = WL_IDLE_STATUS;
#endif

OneWire oneWire(2);
DallasTemperature sensors(&oneWire);

const int analogInPin = A2;  // Analog input pin that sensors is attached to (DEFAULT=A2)  
int readingDelay = 10;  // Delay between each reading (DEFAULT=10)  
int readingsPerSample = 10;  // Number of reaings per sample / loop (DEFAULT=10)  
boolean singleRead = false;  // Series of readings (False) or single reading (TRUE) (DEFAULT=FALSE)  

//vars  
int sensorValue = 0; // value read from the pot  
int outputValue = 0;  
int ledValue = 0;  
int sval;  
int sensorAvg;  
int tenTot; 

char server[] = "www.iot-detroit.org";
IPAddress local_ip;

// Initialize the client library
WiFiClient client;

void setup() {

  sensors.begin();
  
  //Initialize serial and wait for port to open:
  Serial.begin(9600); 
  
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    // don't continue:
    while(true);
  } 
  
  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) { 
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
    status = WiFi.begin(ssid, pass);
  
    // wait 10 seconds for connection:
    delay(10000);
  } 
  Serial.println("Connected to wifi");
  printWifiStatus();
  
  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {

    // Make an HTTP request:
    client.print("GET HTTP/1.1\r\n");
    client.print("Host: www.iot-detroit.org\r\n");
    client.print("Connection: close\r\n\r\n");
    client.stop();
  }
}
void loop()
{
  sensors.requestTemperatures();
  
  float currentTemp;
  currentTemp = sensors.getTempCByIndex(0);


 if(!singleRead){  
   //SAMPLE OF 10 READINGS   
   for (int i=0; i<readingsPerSample; i++){  //repeat number of times defined in setup  
     sval = analogRead(analogInPin);  //take single reading  
     tenTot = tenTot + sval;  //add up readings  
     delay(readingDelay);  //delay between readings as defined in setup. should be non 0  
   }  
   sensorAvg = (tenTot / 10);  //divide the total  
   tenTot = 0; //reset total variable  
   outputValue = sensorAvg;  //define smoothed, averaged reading  
 }else{   
   //STRAIGHT READINGS //only do this if singleRead=true   
   sensorValue = analogRead(analogInPin);  
   outputValue = sensorValue;  
 }  

  // if there are incoming bytes available 
  // from the server, read them and print them:
  while (client.available()&& status == WL_CONNECTED) {
    char c = client.read();
    Serial.write(c);
  }
  client.flush();
  client.stop();

  if (client.connect(server,80) == 1) {

    // HTTP requests are very picky on the format so pay attention
    // to everyghing including spaces!!
    client.print( "GET /arduino-test1/arduino-iot-test-july2015/addsensordata.php?");
    client.print("temp1=");
    client.print( currentTemp );
    client.print("&");
    client.print("photo1=");
    client.print( outputValue );
    client.print( " HTTP/1.1\r\n");
    client.print( "Host: www.iot-detroit.org\r\n\r\n" );
    
    Serial.print( "GET /arduino-test1/arduino-iot-test-july2015/addsensordata.php?");
    Serial.print("temp1=");
    Serial.print( currentTemp );
    Serial.print("&");
    Serial.print("photo1=");
    Serial.print( outputValue );
    Serial.print( " HTTP/1.1\r\n");
    Serial.print( "Host: www.iot-detroit.org\r\n" );

  }
  else {
    Serial.println("Disconnected");
  }
  
  delay(10000);
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
