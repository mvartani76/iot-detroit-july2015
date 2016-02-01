#include <SPI.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>

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
float currentTemp;

// IBM Internet of Things Information
// Update MAC as needed for your device
byte mac[]    = {0x78, 0xC4, 0x0E, 0x01, 0xC9, 0x78 };
char macstr[] = "78C40E01C978";

char servername[]="quickstart.messaging.internetofthings.ibmcloud.com";
String clientName = String("d:quickstart:ArduinoWiFiShield:") + macstr;
String topicName = String("iot-2/evt/status/fmt/json");

// Initialize the client library
WiFiClient wClient;

PubSubClient client(servername, 1883, 0, wClient);

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
  
    // wait 5 seconds for connection:
    delay(5000);
  } 

  Serial.println("Connected to wifi");
  printWifiStatus();
}
void loop()
{
  char clientStr[44];
  clientName.toCharArray(clientStr,44);
  char topicStr[26];
  topicName.toCharArray(topicStr,26);
  
  sensors.requestTemperatures();
  
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

  if (!client.connected()) {
    Serial.print("Trying to connect to: ");
    Serial.println(clientStr);
    client.connect(clientStr);
  }
  if (client.connected() ) {
    String json = buildJson();
    char jsonStr[200];
    json.toCharArray(jsonStr,200);
    boolean pubresult = client.publish(topicStr,jsonStr);
    Serial.print("attempt to send ");
    Serial.println(jsonStr);
    Serial.print("to ");
    Serial.println(topicStr);
    if (pubresult)
      Serial.println("successfully sent");
    else
      Serial.println("unsuccessfully sent");
  }
  delay(5000);
}

String buildJson() {
  String data = "{";
  data+="\n";
  data+= "\"d\": {";
  data+="\n";
  data+="\"myName\": \"Arduino\",";
  data+="\n";
  data+="\"Temperature\": ";
  data+=(float)currentTemp;
  data+= ",";
  data+="\n";
  data+="\"Light Value\": ";
  data+=(int)outputValue;
  data+= ",";
  data+="\n";
  data+="}";
  data+="\n";
  data+="}";
  return data;
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
