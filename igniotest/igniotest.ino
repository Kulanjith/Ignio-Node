#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>



WiFiUDP ntpUDP;

const long utcOffsetInSeconds = 19800;
NTPClient timeClient(ntpUDP,"pool.ntp.org",utcOffsetInSeconds);

void setup() {
Serial.begin(115200); //Serial connection
timeClient.begin();
WiFi.begin("SLT-4G-7A56", "Y61E9J076QR"); //WiFi connection
while (WiFi.status() != WL_CONNECTED) { //Wait for the WiFI connection completion
 delay(500);
 Serial.println("Waiting for connection");
 }
}
void loop() {

  
if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
DynamicJsonBuffer JSONbuffer; //Declaring static JSON buffer
JsonObject& JSONencoder = JSONbuffer.createObject();
JSONencoder["deviceId"] = "NODEIGNIOF101";

timeClient.update();
String current_date_time = timeClient.getFormattedDate();
int splitT = current_date_time.indexOf("T");
String epoch = current_date_time.substring(0, splitT) + " " + current_date_time.substring(splitT+1, current_date_time.length()-1);;
Serial.println(epoch);


JsonArray& sensorData = JSONencoder.createNestedArray("sensorData");
//JSON array
    //for(int i=0; i<5; i++){


        JsonObject& object = sensorData.createNestedObject();
           object["temperature"] =  30.24 ;
           object["co_percentage"] =  10.34 ;
           object["lp_gas_percentage"] =  29.24 ;
           object["particle_percentage"] =  12.34 ;
           object["epoch"] =  epoch ;
     // }



    
    
       
JSONencoder["epoch"] = epoch;
char JSONmessageBuffer[1200];
JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
//Serial.println(JSONmessageBuffer);
HTTPClient http; //Declare object of class HTTPClient

http.begin("http://192.168.1.103:8082/api/device/data/"); //Specify request destination
http.addHeader("Content-Type", "application/json"); //Specify content-type header
http.POST(JSONmessageBuffer); //Send the request
String payload = http.getString(); //Get the response payload
//Serial.println("jjjj"); //Print HTTP return code
Serial.println(payload); //Print request response payload
http.end(); //Close connection
   } else {
       Serial.println("Error in WiFi connection");
  }
  delay(15000); //Send a request every 30 seconds
}
