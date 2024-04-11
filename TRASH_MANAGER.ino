#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

WiFiClient wifiClient;
const char* ssid = "RealmeC1";
const char* password = "12345678";

#define trigP D1
#define echoP D2

long duration;
int distance;



void setup () {

  pinMode(trigP,OUTPUT);
  pinMode(echoP, INPUT);
  

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);
    Serial.print("Connecting..");

  }

}

void loop() {


  digitalWrite(trigP,LOW);
  delayMicroseconds(2);
  digitalWrite(trigP, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigP,LOW);

  duration = pulseIn(echoP, HIGH);
  distance = duration*0.034/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(1000);

  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    HTTPClient http;  //Declare an object of class HTTPClient


    String url = "http://trash-manager.herokuapp.com/current_status/";
    char str_dist[20];

    itoa(distance,str_dist,10);

    String stringThree;
    stringThree =  url + str_dist;

     
    http.begin(wifiClient,stringThree);  //Specify request destination
    int httpCode = http.GET();     //Send the request                                                           

    if (httpCode > 0) { //Check the returning code

      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload

    }

    http.end();   //Close connection

  }

  delay(30000);    //Send a request every 30 seconds

}