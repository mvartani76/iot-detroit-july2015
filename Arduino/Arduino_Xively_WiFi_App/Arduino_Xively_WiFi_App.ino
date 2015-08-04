#include <b64.h>
#include <HttpClient.h>

#include <CountingStream.h>
#include <Xively.h>
#include <XivelyClient.h>
#include <XivelyDatastream.h>
#include <XivelyFeed.h>

/*
##Xively WiFi Sensor Tutorial##
This sketch is designed to take sensors (from photocell) and upload the values to Xively
at consistant intervals. At the same time it gets a setable value from Xively to adjust the brigthness
of an LED. This sketch is reusable and can be adapted for use with many different sensors.
Derived from Xively Ardino Sensor Client by Sam Mulube.
 
By Calum Barnes 3-4-2013
BSD 3-Clause License - [http://opensource.org/licenses/BSD-3-Clause]
Copyright (c) 2013 Calum Barnes
*/

#include <SPI.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#include <HttpClient.h>
#include <Xively.h>

#include <OneWire.h>
#include <DallasTemperature.h>

#ifndef __CREDENTIALS_H__
#define __CREDENTIALS_H__
char pass[] = "your-password"; //password Wi-Fi
char ssid[] = "your-ssid"; //name Wi-Fi
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

// Initialize the client library
WiFiClient client;
 
// Your Xively key to let you upload data
char xivelyKey[] = "YOUR-XIVELY-KEY";
//your xively feed ID -- FILL IN YOUR XIVELY FEED NUMBER BELOW
#define xivelyFeed 1234567890
//datastreams
char tempsensor_ID[] = "TEMP_SENSOR_CHANNEL";
char photosensor_ID[] = "LIGHT_SENSOR_CHANNEL";
 
// Analog pin which we're monitoring (0 and 1 are used by the Ethernet shield)
#define sensorPin A2

// Define the strings for our datastream IDs
XivelyDatastream datastreams[] = {
  XivelyDatastream(tempsensor_ID, strlen(tempsensor_ID), DATASTREAM_FLOAT),
  XivelyDatastream(photosensor_ID, strlen(photosensor_ID), DATASTREAM_FLOAT),
};
// Finally, wrap the datastreams into a feed
XivelyFeed feed(xivelyFeed, datastreams, 2 /* number of datastreams */);
 
XivelyClient xivelyclient(client);

void setup() {
 
  // put your setup code here, to run once:
  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  sensors.begin();
  
  //pin setup
  pinMode(analogInPin, INPUT);
  
  Serial.println("Starting single datastream upload to Xively...");
  Serial.println();
 
  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) { 
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    //status = WiFi.begin(ssid, keyIndex, pass);
    status = WiFi.begin(ssid,pass);
    // wait 10 seconds for connection:
    delay(10000);
  } 
  Serial.println("Connected to wifi");
  printWifiStatus();
}
 
void loop() {

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
  
///////////////////////////////////////////////////////
  //put temp and photo sensor values into xively datastreams
  datastreams[0].setFloat(currentTemp);
  datastreams[1].setFloat(outputValue);

  //print the sensor valye
  Serial.print("Read sensor value ");
  Serial.println(datastreams[0].getFloat());
 
  //send values to xively
  Serial.println("Uploading it to Xively");
  int ret = xivelyclient.put(feed, xivelyKey);
  //return message
  Serial.print("xivelyclient.put returned ");
  Serial.println(ret);
  Serial.println("");
  
  //delay between calls
  delay(15000);
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
