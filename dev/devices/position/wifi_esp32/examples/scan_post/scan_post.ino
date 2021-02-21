#include <stdlib.h>
#include <string.h>

#include <WiFi.h>

#include <HTTPClient.h>

#include <ArduinoJson.h>

// Eugeune's mobile network
char *AP_SSID = "Redmi";
char *AP_PWD = "toto1234";

const char  *serverAddress = "https://www.googleapis.com/geolocation/v1/geolocate?key=AIzaSyDMnY8W47H_ztdC4sJjo2Z9_bu2y9-zEPM";
int          port = 8080;

String mac_address[2];
int recep_power[2];

double location_lat  = 0.000000;
double location_lng  = 0.000000;
long   accuracy      = 0;

void setup(){

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

    run();
}

void loop()
{}

void run(){

    wifi_scan();

    if(postDataToServer() == -1){
      Serial.println("Error post data");
    }

    Serial.println("");

    Serial.print("Latitude (DD) : ");
    Serial.println(location_lat);
    
    Serial.print("Longitude (DD) : ");
    Serial.println(location_lng);

    Serial.print("Accuracy (m) : ");
    Serial.print(accuracy/50);

    Serial.println("");
}

int postDataToServer(){
 
  Serial.println("Posting JSON data to server...");

  // Block until we are able to connect to the WiFi access point
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;   
     
    http.begin(serverAddress);  
    http.addHeader("Content-Type", "application/json");           
     
    StaticJsonDocument<256> req;

    JsonArray wifiAccessPoints = req.createNestedArray("wifiAccessPoints");

    Serial.println("Filling Json with first wifi object...");
    Serial.println("macAdress : " + mac_address[0]);
    Serial.print("Strength  : ");
    Serial.println(recep_power[0]);
    
    JsonObject wifiAccessPoints_0               = wifiAccessPoints.createNestedObject();
    wifiAccessPoints_0["macAddress"]            = mac_address[0];
    wifiAccessPoints_0["signalStrength"]        = recep_power[0];
    wifiAccessPoints_0["signalToNoiseRatio"]    = 0;

    delay(1000);

    Serial.println("Filling Json with second wifi object...");
    Serial.println("macAdress : " + mac_address[1]);
    Serial.print("Strength  : ");
    Serial.println(recep_power[1]);
    
    JsonObject wifiAccessPoints_1               = wifiAccessPoints.createNestedObject();
    wifiAccessPoints_1["macAddress"]            = mac_address[1];
    wifiAccessPoints_1["signalStrength"]        = recep_power[1];
    wifiAccessPoints_1["signalToNoiseRatio"]    = 0;

    delay(1000);
     
    String requestBody;
    serializeJson(req, requestBody);

    Serial.println("");
    Serial.print(requestBody);
    Serial.println("");
     
    int httpResponseCode = http.POST(requestBody);

    while(true){
        if(httpResponseCode>0){
           
          String response = http.getString(); 

          Serial.println(httpResponseCode);   
          Serial.println(response);

          // Parse Json response File and get lat, lng and accuracy
          StaticJsonDocument<128> res;
          deserializeJson(res, response);

          location_lat = res["location"]["lat"];
          location_lng = res["location"]["lng"];

          accuracy = res["accuracy"];
          
          return 0;
      }
      else {
       
        Serial.printf("Error occurred while sending HTTP POST");
        return -1;
      }
    }
  }

  return -1;
}

void wifi_scan(){
    
    Serial.println("scan start");
    
    int wifi_saved = 0;
    
    uint8_t *bssid;
    char bssid_str[18];

    int power;

    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    
    if (n == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        
        for (int i = 0; i < n; ++i) {
            
            bssid = WiFi.BSSID(i);
            sprintf(bssid_str, "%X-%X-%X-%X-%X-%X",bssid[5], bssid[4], bssid[3], bssid[2], bssid[1], bssid[0]); 

            power = int(WiFi.RSSI(i));

            
            // if wifi isn't mobile
            if(bssid_str[9] == 'B' && bssid_str[10] == 'D' && wifi_saved < 2){

               // Serial.print(power);
               // Serial.print(", ");
               // Serial.print(wifi_saved);
               // Serial.print(", ");
                
                mac_address[wifi_saved] = bssid_str;
                recep_power[wifi_saved] = power;
                wifi_saved++;
            }

            // Print SSID, RSSI, BSSID and encryption mode for each network found
            
            Serial.print(i + 1);
            Serial.print(": ");
            
            Serial.print(WiFi.SSID(i));

            Serial.print(", Power (dBm) :");
            Serial.print(power);
            
            Serial.print(", BSSID: ");
            Serial.print(bssid_str);

            Serial.print(", Encryption Type : ");
            Serial.println(WiFi.encryptionType(i));
            
            delay(10);
        }
    }
    Serial.println("");

    // Wait for 5s before scanning again
    delay(5000);
}
