#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>

// Eugeune's mobile network
const char *AP_SSID = "Minn";
const char *AP_PWD = "arun5505";

const char  *serverAddress  = "https://www.googleapis.com/geolocation/v1/geolocate?key=AIzaSyDMnY8W47H_ztdC4sJjo2Z9_bu2y9-zEPM";
int          port           = 8080;
 
void setup() {
  Serial.begin(115200);
    
  WiFi.begin(AP_SSID, AP_PWD);
  
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Setup done");
}
 
void loop() {
  Serial.println("Posting JSON data to server...");

  // Block until we are able to connect to the WiFi access point
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;   
     
    http.begin(serverAddress);  
    http.addHeader("Content-Type", "application/json");           
     
    StaticJsonDocument<256> req;

    JsonArray wifiAccessPoints = req.createNestedArray("wifiAccessPoints");

    // Warning : mac Adress and Signal Strenght have to be updated before using this code
    JsonObject wifiAccessPoints_0           = wifiAccessPoints.createNestedObject();
    wifiAccessPoints_0["macAddress"]        = "80-EA-9D-90-CD-5A";
    wifiAccessPoints_0["signalStrength"]    = -59;
    
    JsonObject wifiAccessPoints_1           = wifiAccessPoints.createNestedObject();
    wifiAccessPoints_1["macAddress"]        = "0-29-74-C5-6F-E6";
    wifiAccessPoints_1["signalStrength"]    = -63;
    
    JsonObject wifiAccessPoints_2           = wifiAccessPoints.createNestedObject();
    wifiAccessPoints_2["macAddress"]        = "20-26-51-B8-62-70";
    wifiAccessPoints_2["signalStrength"]    = -65;
     
    String requestBody;
    serializeJson(req, requestBody);

    Serial.println("");
    Serial.print(requestBody);
    Serial.println("");
     
    int httpResponseCode = http.POST(requestBody);

    if(httpResponseCode>0){
       
      String response = http.getString(); 

      Serial.println(httpResponseCode);   
      Serial.println(response);
    }
    else {
      Serial.printf("Error occurred while sending HTTP POST");
    }

    while(1){}
  }
}
