#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <DHT.h>
 
#define FIREBASE_HOST "\" // Firebase host
#define FIREBASE_AUTH "\" //Firebase Auth code
#define WIFI_SSID "\" //Enter your wifi Name
#define WIFI_PASSWORD "" // Enter your password

#define DHTPIN D2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11 


DHT dht(DHTPIN, DHTTYPE);
 
void setup() {
  Serial.begin(9600);
  
  dht.begin();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.println("Connected.");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  //Firebase.set("LED_STATUS",0);
  Firebase.setFloat("Humidity: ", 0);
  Firebase.setFloat("Temperature: ", 0); 
}
 
void loop() {
  delay(1000);
  float h = dht.readHumidity();
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println("%");
  Firebase.setFloat("humadity",h);

   float t = dht.readTemperature(); 
  Serial.print("Temperature: "); 
  Firebase.setFloat("Temperature: ", t); 
  Serial.print(t); 
  Serial.println("°C"); 
} 
