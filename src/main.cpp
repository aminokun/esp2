#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <tds.h>

// const char* ssid = "FRITZ!Box 7530 WT";
// const char* password = "89580715389315208415";

const char* ssid = "NETLAB-OIL010";
const char* password = "DesignChallenge";

WiFiServer server(80);

int LED_RED = D0;
int LED_GREEN = D1;
int BUZZER = D5;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client connected");
    String result = client.readStringUntil('\r');
    client.flush();
    Serial.println(result);

    if (result.indexOf("GET /led/on") >= 0) {
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(LED_RED, HIGH);
      digitalWrite(LED_GREEN, HIGH);

    } else if (result.indexOf("GET /led/off") >= 0) {
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_GREEN, LOW);

    } else if (result.indexOf("GET /Buzzer/on") >= 0) {
      digitalWrite(BUZZER, HIGH);


    } else if (result.indexOf("GET /Buzzer/off") >= 0){
      digitalWrite(BUZZER, LOW);
    } else {
      client.println("Invalid request");
    }

    client.stop();
    Serial.println("Client disconnected");
  }
}