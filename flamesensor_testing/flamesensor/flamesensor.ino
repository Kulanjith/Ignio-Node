#include<SoftwareSerial.h>

int sensorPin = D0; // select the input pin for the LDR
int sensorValue; // variable to store the value coming from the sensor
int led =D2 ; // Output pin for LED
int buzzer = D4; // Output pin for Buzzer

void setup() {

// declare the ledPin and buzzer as an OUTPUT:

pinMode(led, OUTPUT);
pinMode(buzzer,OUTPUT);
Serial.begin(9600);
}
void loop()
{

Serial.println("Flame Sensor Testing.........");
sensorValue = digitalRead(sensorPin);
//Serial.println(sensorValue);

if (sensorValue == 0){
Serial.println(".......Fire Detected.....");
Serial.println("........WARNING.......");
digitalWrite(led,HIGH);
digitalWrite(buzzer,HIGH);
delay(1000);

}

digitalWrite(led,LOW);

digitalWrite(buzzer,LOW);
delay(1000);
delay(sensorValue);

}
