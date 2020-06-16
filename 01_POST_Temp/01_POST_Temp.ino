#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// TODO: Insert WLAN-SSID-PW
const char* ssid = "*****";
const char* password = "*****";
 
void setup() {
  
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
 
   http.begin("http://benz-prints.com:3004/dnd/user/login");
   http.addHeader("Content-Type", "application/json");
  
   int httpCode = http.POST("{email: 'oliver.benz@outlook.com', password: ''}");
   String payload = http.getString();
 
   Serial.println(httpCode);
   Serial.println(payload);
 
   http.end();
  }else{
    Serial.println("Error in WiFi connection");   
 }
 
  delay(2000);
}
