#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <string.h> 

// Set these to run example.
#define WIFI_SSID "Device-Northwestern"
#define LOCK_PIN 23

void setup() {
  Serial.begin(9600);

  pinMode(LOCK_PIN, OUTPUT);
  

  // connect to wifi.
  WiFi.begin(WIFI_SSID);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
}


void loop() {
    // Checks wifi connection
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("connection failed");
        return;
    }

    HTTPClient http;
    http.begin("https://dooropener-699b5.firebaseio.com/Test.json");
    int httpCode = http.GET();                                   
 
    while (httpCode > 0) { //Check for the returning code
 
        char payload = http.getString().charAt(0);
        Serial.println(httpCode);
        Serial.println(payload);

        if (payload == '0') {
          digitalWrite(LOCK_PIN, LOW);
          Serial.println("True");
          }
        else {
          digitalWrite(LOCK_PIN, HIGH);
          } 

        int httpCode = http.GET(); 
        delay(1000); 
      }
 

    Serial.println("Error on HTTP request");

    http.end();
    delay(1000);

    Serial.println();
    Serial.println("closing connection");
}
