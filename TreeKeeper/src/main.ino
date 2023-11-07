/*
    TreeKeeper - a wildfire early warning and detection system using arduino and ML.
    TODO
    [x] Record all sensor data
    [x] Forward sensor data to cloud on a regular basis (~20secs)
*/


#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>


//wifi creds
#define WIFI_SSID "SLT_H"
#define WIFI_PASSWORD "YahampathH8282"

//firebase creds
#define FIREBASE_HOST "treekeeper-fe946-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "1FiwxCYFSW10qXw4qCkXS4A2yTIAkvlIpdy9Tvqm"

//pins
#define DHT_PIN D2
#define SOIL_PIN A0
#define FIRE_PIN D5
#define SMOKE_PIN D6


#define DHTTYPE DHT11

DHT dht(DHT_PIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
    //setup pins 
  pinMode(DHT_PIN, INPUT);
  pinMode(SOIL_PIN, INPUT);
  pinMode(FIRE_PIN, INPUT);
  pinMode(SMOKE_PIN, INPUT);

  //connect to wifi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    
  }
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  dht.begin();

}

void loop() {

  //read all sensors
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();
  int soil = analogRead(SOIL_PIN);
  int fire = digitalRead(FIRE_PIN);
  int smoke = digitalRead(SMOKE_PIN);

  //write to firebase
  Firebase.setFloat("temp", temp);
  Firebase.setFloat("humidity", humidity);
  Firebase.setInt("soil", soil);
  Firebase.setInt("fire", fire);
  Firebase.setInt("smoke", smoke);

  //print to serial
  Serial.print("Temperature: ");
  Serial.println(temp);
  Serial.print("Humidity: ");
  Serial.println(humidity);
  Serial.print("Soil: ");
  Serial.println(soil);
  Serial.print("Fire: ");
  Serial.println(fire);
  Serial.print("Smoke: ");
  Serial.println(smoke);

  //wait 20 secs
  delay(1000);


}
