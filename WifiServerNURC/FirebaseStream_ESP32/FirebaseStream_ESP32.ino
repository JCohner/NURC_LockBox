//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseStream_ESP32 is a sample that stream bitcoin price from a
// public Firebase and optionally display them on a OLED i2c screen.

#include <IOXhop_FirebaseESP32.h>
#include <WiFi.h>

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
  
  Firebase.begin("dooropener-699b5.firebaseio.com");
  Firebase.stream("/Test", [](FirebaseStream stream) {
    String eventType = stream.getEvent();
    eventType.toLowerCase();
     
    Serial.print("event: ");
    Serial.println(eventType);
    if (eventType == "put") {
      Serial.print("data: ");
      Serial.println(stream.getDataString());
      String path = stream.getPath();
      String data = stream.getDataString();
    }
  });  
}


void loop() {
 
}
