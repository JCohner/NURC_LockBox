#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>

// Set these to run example.
#define WIFI_SSID "Device-Northwestern"

void setup() {
  Serial.begin(9600);

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
 
    if (httpCode > 0) { //Check for the returning code
 
        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
      }
 
    else {
      Serial.println("Error on HTTP request");
    }

    http.end();

    Serial.println();
    Serial.println("closing connection");
}
