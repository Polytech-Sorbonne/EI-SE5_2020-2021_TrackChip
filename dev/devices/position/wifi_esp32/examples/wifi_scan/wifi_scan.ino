#include <SPI.h>
#include <WiFi.h>

void setup()
{
    Serial.begin(115200);

    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    Serial.println("Setup done");
}

void loop()
{
    Serial.println("scan start");
        
    uint8_t *bssid;
    char bssid_str[18];

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

            // Print SSID, RSSI, BSSID and encryption mode for each network found
            
            Serial.print(i + 1);
            Serial.print(": ");
            
            Serial.print(WiFi.SSID(i));

            Serial.print(", Power (dBm) :");
            Serial.print(WiFi.RSSI(i));
            
            Serial.print(", BSSID: ");
            Serial.print(bssid_str);

            Serial.print(", Encryption Type : ");
            printEncryptionType(WiFi.encryptionType(i));
            
            delay(10);
        }
    }
    Serial.println("");

    // Wait for 5s before scanning again
    delay(5000);
}

void printEncryptionType(int thisType) {
  // read the encryption type and print out the name:
  switch (thisType) {
    case 5:
      Serial.println("WEP");
      break;
    case 2:
      Serial.println("WPA");
      break;
    case 4:
      Serial.println("WPA2");
      break;
    case 7:
      Serial.println("None");
      break;
    case 8:
      Serial.println("Auto");
      break;
    default:
      Serial.println("Unknown");
      break;
  }
}
