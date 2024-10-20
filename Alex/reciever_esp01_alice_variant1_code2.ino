#include <ESP8266WiFi.h>

const char* ssid = "Airtel_arun_7500";
const char* password = "7087523885s";

WiFiServer server(1234);

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

  // Print the IP address
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Start the server
  server.begin();
  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Client connected");

    while (client.connected()) {
      while (client.available()) {
        char request = client.read();
        Serial.println(request);
      }

      // Send a response back to the client
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println();
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("<p>Value received</p>");
      client.println("</html>");
    }

    // Disconnect the client if it has no data and is not connected anymore
    if (!client.connected()) {
      Serial.println("Client disconnected");
    }
  }
}
