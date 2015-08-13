#include <Bridge.h>
#include <Console.h>
#include <FileIO.h>
#include <HttpClient.h>
#include <Mailbox.h>
#include <Process.h>
#include <YunClient.h>
#include <YunServer.h>

#include <SPI.h>

#include <Bridge.h>

#include <OneWire.h>
#include <DallasTemperature.h>

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
YunClient client;

void setup() { 
  
  sensors.begin();
  pinMode(13,OUTPUT);  
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);

  Console.begin();

  while(!Console);  // wait for network serial to open
  
  Console.println("\nStarting connection to server...");
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
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }
  client.flush();
  client.stop();

  if (client.connect(server,80) == 1) {

    // HTTP requests are very picky on the format so pay attention
    // to everyghing including spaces!!
    client.print( "GET /iot-detroit-july2015/php/SensorRead_MySQL/addsensordata.php?");
    client.print("temp1=");
    client.print( currentTemp );
    client.print("&");
    client.print("photo1=");
    client.print( outputValue );
    client.print("&");
    client.print("DeviceType=");
    client.print("DraginoYunWiFi" );    
    client.print( " HTTP/1.1\r\n");
    client.print( "Host: www.iot-detroit.org\r\n\r\n" );
    
    Console.print( "GET /iot-detroit-july2015/php/SensorRead_MySQL/addsensordata.php?");
    Console.print("temp1=");
    Console.print( currentTemp );
    Console.print("&");
    Console.print("photo1=");
    Console.print( outputValue );
    Console.print("&");
    Console.print("DeviceType=");
    Console.print(" ArduinoUNOWiFi" );
    Console.print( " HTTP/1.1\r\n");
    Console.print( "Host: www.iot-detroit.org\r\n" );

  }
  else {
    Console.println("Disconnected");
  }
  
  delay(10000);
}
