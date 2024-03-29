#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>


 
#include "index.h" //Our HTML webpage contents with javascripts
 
#define LED 2  //On board LED
 
//SSID and Password of your WiFi router
const char* ssid = "Superfast";
const char* password = "deviiphone";
int led = D2; // Output pin for LED
int buzzer = D0; // Output pin for Buzzer

ESP8266WebServer server(80); //Server on port 80
 
//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

//const int oneWireBus = 4;
//OneWire oneWire(oneWireBus); 
//DallasTemperature sensors(&oneWire);

void handleADC() {
  
  //sensors.requestTemperatures(); 
 // float temperatureC = sensors.getTempCByIndex(0);
 // float temperatureF = sensors.getTempFByIndex(0);
 
  //int a = analogRead(A0);
  float h = analogRead(A0);

  String adcValue = String(h);
 
 digitalWrite(LED,!digitalRead(LED)); //Toggle LED on data request ajax
 delay(2000);
  
 Serial.print("Sensor Value: ");
 Serial.println(h);
  if (h>350){
     
     digitalWrite(led,HIGH);
     digitalWrite(buzzer,HIGH);
     

    }
  else {
    digitalWrite(led,LOW);
    digitalWrite(buzzer,LOW);
    }

 server.send(200, "text/plane", adcValue); //Send ADC value only to client ajax request
}
//==============================================================
//                  SETUP
//==============================================================
void setup(void){
  
pinMode(led, OUTPUT);
pinMode(buzzer,OUTPUT);
digitalWrite(led,LOW);
digitalWrite(buzzer,LOW);
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");
 
  //Onboard LED port Direction output
  pinMode(LED,OUTPUT); 
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
  server.on("/readADC", handleADC); //This page is called by java Script AJAX
 
  server.begin();                  //Start server
  Serial.println("HTTP server started");
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  server.handleClient();          //Handle client requests
}
