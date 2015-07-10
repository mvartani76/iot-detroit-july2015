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


//IPAddress server(37,60,225,35);
char server[] = "www.iot-detroit.org";
IPAddress local_ip;

// Initialize the client library
WiFiClient client;

int looped = 1;

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
    Serial.println("connected to server");
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
  Serial.print("Temp = ");
  Serial.print("\t");
  Serial.println(currentTemp,2);

  if (client.connect(server,80)) {
    Serial.println("Connect");
    client.print( "GET /arduino-test1/arduino-iot-test-july2015/addsensordata.php?");
    client.print("temp1=");
    client.print( currentTemp );
    client.print("&");
    client.print("photo1=");
    client.print( currentTemp );
    client.print( " HTTP/1.1\r\n");
    client.print( "Host: www.iot-detroit.org\r\n" );
    client.print( "Content-Type: application/x-www-form-urlencoded\r\n" );
    client.print( "Connection: close\r\n\r\n" );

    client.stop();
  }
  else {
    Serial.println("Disconnected");
    client.stop();
  }

  // if there are incoming bytes available 
  // from the server, read them and print them:
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
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
