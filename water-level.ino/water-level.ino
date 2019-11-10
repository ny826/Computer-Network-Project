#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
  
char ssid[] = "yadav"; 
char pass[] = "yadav826"; 

const int trigger = 16;
const int echo = 5;
int Enable = 4;

int Input1 = 0;

int Input2 = 2;
long Time;
float distanceinCM;
WiFiClient  client;

unsigned long ChannelField = 861229; 
const int ChannelFieldNo = 1; 
const char * APIKey = "YSGZSIJQG0GBWQTI"; 
void setup()
{
  Serial.begin(115200);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(Enable, OUTPUT);
  pinMode(Input1, OUTPUT);
  pinMode(Input2, OUTPUT);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
}

void loop()
{
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED)
    {
      
      Serial.print("#");
      delay(500);
    }
    Serial.println("\nConnected.");

 
  digitalWrite(trigger, LOW);
  delay(1);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  Time = pulseIn(echo, HIGH);
  distanceinCM = Time * 0.034;
  distanceinCM = distanceinCM / 2;
  Serial.print("Distance in cm: ");
  Serial.println(distanceinCM);
   if(distanceinCM>5){
   ThingSpeak.writeField(ChannelField, ChannelFieldNo, distanceinCM, APIKey);

      motoron();
  }
  else{
    motoroff();
  }
  
  delay(1000);
}

void motoron()
{

  digitalWrite(Enable, HIGH);
digitalWrite(Input1, HIGH);
digitalWrite(Input2, LOW);



  Serial.println(digitalRead(Enable));
  Serial.println(digitalRead(Input1));
  Serial.println(digitalRead(Input2));

  delay(1000);

  

}

void motoroff()
{
 
  digitalWrite(Input1, LOW);
  digitalWrite(Input2, LOW);
  Serial.println(digitalRead(Enable));
  Serial.println(digitalRead(Input1));
  Serial.println(digitalRead(Input2));

  delay(1000);
}
