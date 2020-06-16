#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

//TODO: Insert WLAN-SSID-PW
const char* ssid = "*****";
const char* password = "*****"

// Setup JSON Parser
const size_t capacity = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + 132;
DynamicJsonDocument doc(capacity);

void setup() {
  // Setup Ping
  pinMode(5, OUTPUT);
  
  Serial.begin(115200);
  delay(10);
 
  // Connect WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.hostname("Name");
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Print the IP address
  Serial.print("IP address: ");
  Serial.print(WiFi.localIP());
}
 
void loop() {
  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
 
    http.begin("http://192.168.0.76:3005/led");
    http.addHeader("Content-Type", "application/json");
    
    int httpCode = http.GET();
    String payload = http.getString();
    deserializeJson(doc, payload);
    JsonObject body = doc.as<JsonObject>();

    Serial.print("Code: ");
    Serial.println(httpCode);
    Serial.println();
    if(httpCode == 200){
      Serial.println("Message: ");
      Serial.print("Success: ");
      Serial.println(body["success"].as<boolean>());
      Serial.print("R: ");
      Serial.println(body["data"]["r"].as<int>());
      Serial.print("G: ");
      Serial.println(body["data"]["g"].as<int>());
      Serial.print("B: ");
      Serial.println(body["data"]["b"].as<int>());

      digitalWrite(5, HIGH);
    } else{
      digitalWrite(5, LOW);
    }
    
   http.end();
  }else{
    Serial.println("Error in WiFi connection");   
 }
 
  delay(2000);
}
