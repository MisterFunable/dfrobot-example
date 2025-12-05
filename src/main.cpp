#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// Replace with your WiFi credentials
const char* ssid = "Gomero";
const char* password = "D4cheap.77!!";

// Built-in LED pin
#define LED_PIN 2

// Create web server on port 80
WebServer server(80);

// HTML for the webpage
const char* html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>ESP32 Control</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            max-width: 600px;
            margin: 50px auto;
            padding: 20px;
            background: #f0f0f0;
        }
        h1 {
            color: #333;
        }
        button {
            background: #4CAF50;
            color: white;
            padding: 15px 32px;
            font-size: 16px;
            border: none;
            border-radius: 4px;
            cursor: pointer;
            margin: 10px;
        }
        button.off {
            background: #f44336;
        }
        button:hover {
            opacity: 0.8;
        }
        .status {
            padding: 20px;
            background: white;
            border-radius: 4px;
            margin: 20px 0;
        }
    </style>
</head>
<body>
    <h1>ESP32 Web Server</h1>
    <div class="status">
        <p>Control the onboard LED from your browser.</p>
    </div>
    <button onclick="fetch('/on')">Turn LED ON</button>
    <button class="off" onclick="fetch('/off')">Turn LED OFF</button>
</body>
</html>
)rawliteral";

// Handle main page
void handleRoot() {
    Serial.println("Request received: /");
    server.send(200, "text/html", html);
}

// Handle LED ON
void handleOn() {
    Serial.println("Request received: /on");
    digitalWrite(LED_PIN, HIGH);
    server.send(200, "text/plain", "LED is ON");
}

// Handle LED OFF
void handleOff() {
    Serial.println("Request received: /off");
    digitalWrite(LED_PIN, LOW);
    server.send(200, "text/plain", "LED is OFF");
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
    
    // Connect to WiFi
    Serial.print("Connecting to WiFi");
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("\nConnected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    
    // Setup web server routes
    server.on("/", handleRoot);
    server.on("/on", handleOn);
    server.on("/off", handleOff);
    
    // Start server
    server.begin();
    Serial.println("Web server started");
}

void loop() {
    server.handleClient();
}