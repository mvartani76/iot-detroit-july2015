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


IPAddress server(37,60,225,35);

// Initialize the client library
WiFiClient client;

int looped = 1;

void setup() {

  sensors.begin();
  
  //Initialize serial and wait for port to open:
  Serial.begin(57600); 
  
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
    Serial.println("connected to server");
    // Make an HTTP request:
    client.println("GET HTTP/1.1");
    client.println("Host: 37.60.225.35");
    client.println("Connection: close");
    client.println();
  }
}
void loop()
{
  sensors.requestTemperatures();
  
  float currentTemp;
  currentTemp = sensors.getTempCByIndex(0);
  Serial.print("Temp = ");
  Serial.print("\t");
  Serial.println(currentTemp,2);
    
  delay(1000);
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
