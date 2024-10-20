#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
const char* ssid = "Statusbrew Guest";
const char* password = "lifeatstatusbrew";


WiFiClient client;

void setup() {
  Serial.begin(9600);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected");

  // Connect to server


void sendToServer(String url, DynamicJsonDocument& jsonDoc) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String jsonData;
    serializeJson(jsonDoc, jsonData);

    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(jsonData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.print("Response code: ");
      Serial.println(httpResponseCode);
      Serial.println("Response: " + response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("Error in WiFi connection");
  }
}

void loop() {
  if (Serial.available()) {
    char received = Serial.read();
    if (received != '\n' && received != '\r') {
      client.print(received);
      char Value = received;  // Debugging line to confirm sent message
    }
  }

  if (!client.connected()) {
    Serial.println("Disconnected from server");
    client.stop();
    delay(1000);
    client.connect(serverIP, serverPort);
  }
  if (Value == A) {
    DynamicJsonDocument jsonDoc(1024);
    String serverURL = "https://pleasant-mullet-unified.ngrok-free.app/fire-sensor/fire-detected";
    jsonDoc["sensor_name"] = "smoke";
    jsonDoc["fire_hazard_level"] = 3;
    jsonDoc["smoke_level"] = sensorValue;
    jsonDoc["temp_level"] = sensorValue;
    sendToServer(serverURL, jsonDoc);
  } 
  // Thermoresistor for temperature threshold (second priority)
  else if (Value == B) {
    DynamicJsonDocument jsonDoc(1024);
    String serverURL = "https://pleasant-mullet-unified.ngrok-free.app/fire-sensor/fire-detected";
    jsonDoc["sensor_name"] = "smoke";
    jsonDoc["fire_hazard_level"] = 2;
    jsonDoc["smoke_level"] = sensorValue;
    jsonDoc["temp_level"] = sensorValue;
    sendToServer(serverURL, jsonDoc);
  } 
  // Smoke sensor (third priority)
  else if (Value == C) {
    DynamicJsonDocument jsonDoc(1024);
    String serverURL = "https://pleasant-mullet-unified.ngrok-free.app/fire-sensor/fire-detected";
    jsonDoc["sensor_name"] = "smoke";
    jsonDoc["fire_hazard_level"] = 1;
    jsonDoc["smoke_level"] = sensorValue;
    jsonDoc["temp_level"] = sensorValue;
    sendToServer(serverURL, jsonDoc);
  } 
  // Parking status (fourth priority)
  else if (Value == D) {
    DynamicJsonDocument jsonDoc(1024);
    String serverURL = "https://pleasant-mullet-unified.ngrok-free.app/parking/update-status/B7";
    jsonDoc["status"] = parking;
    sendToServer(serverURL, jsonDoc);
  } 
  // LDR for garbage overflow detection (lowest priority)
  else if (Value == E) {
    DynamicJsonDocument jsonDoc(1024);
    String serverURL = "https://pleasant-mullet-unified.ngrok-free.app/garbage-collection/garbage-overflow";
    jsonDoc["sensor_name"] = "garbage01";
    sendToServer(serverURL, jsonDoc);
  }

  delay(3000); // Wait 3 seconds before the next loop
}

}
