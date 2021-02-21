#include "TrackChip.h"

TrackChip::TrackChip() {
	// Inutile de print ici, la liaison série est initialisée plus tard
	this->gps = new GROVE11302();
	Wire.begin();
	AP_SSID	= "Redmi";
	AP_PWD 	= "toto1234";
}

TrackChip::~TrackChip() {}

void TrackChip::send_data(String s) {
	// Envoyer uniquement des chaines de la forme :
	// 004A882F000398DC2F 

	// insérer vérification

	Wisol wisol = Wisol();
	wisol.send_string_data(s);
}

float TrackChip::get_altitude() {
	static bool init = true; 
	static BMP180I2C bmp = BMP180I2C(BMP_I2C_ADDRESS);

	if (init) {
		bmp.init();
		init = false;
	}

	return bmp.computeAltitude();
}

String TrackChip::get_position() {
	gps->get_data_line();
	String res = (char*) (gps->buffer);

	return res;
}

void TrackChip::connect_to_wifi() {
	Serial.println("connection_to_wifi...");
	Serial.println(AP_SSID);
	Serial.println(AP_PWD);
	
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

void TrackChip::wifi_scan() {
	Serial.println("Starting scan");
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

    int test_to_delete = 0;
		for (int i = 0; i < n; ++i) {
			
			bssid = WiFi.BSSID(i);
			sprintf(bssid_str, "%X-%X-%X-%X-%X-%X",bssid[5], bssid[4], bssid[3], bssid[2], bssid[1], bssid[0]); 
			power = int(WiFi.RSSI(i));
      
      //Serial.print("test BD google : ");
      //Serial.print(bssid_str[9]);
      //Serial.println(bssid_str[10]);
      
      /*if (test_to_delete < 2){
        Serial.println("enter test to delete");
        for(int k = 0; k<TAILLE_ADRESSE_MAC ;k++){
          //Serial.print("part of MAc is : ");
           bssidtab[test_to_delete][k] = bssid[TAILLE_ADRESSE_MAC-1-k];
           Serial.println(bssidtab[test_to_delete][k]);
          }
          test_to_delete++;
      }*/
			// select fix WiFi which are in google database
			if(bssid_str[9] == 'B' && bssid_str[10] == 'D' && wifi_saved < NB_ADRESSE_MAC){
				for(int k = 0; k<TAILLE_ADRESSE_MAC ;k++){
            Serial.print("part of MAc is : ");
            bssidtab[wifi_saved][k] = bssid[TAILLE_ADRESSE_MAC-1-k];
            Serial.println(bssidtab[wifi_saved][k]);
          };
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
			Serial.println(bssid_str);
			
			delay(10);
		}
		delay(5000);	 // Wait for 5s before scanning again
	}
}	

int TrackChip::send_mac_and_get_pos() {
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
		Serial.print("Strength	: ");
		Serial.println(recep_power[0]);
		
		JsonObject wifiAccessPoints_0				= wifiAccessPoints.createNestedObject();
		wifiAccessPoints_0["macAddress"]			= mac_address[0];
		wifiAccessPoints_0["signalStrength"]		= recep_power[0];
		wifiAccessPoints_0["signalToNoiseRatio"]    = 0;

		delay(1000);

		Serial.println("Filling Json with second wifi object...");
		Serial.println("macAdress : " + mac_address[1]);
		Serial.print("Strength	: ");
		Serial.println(recep_power[1]);
		
		JsonObject wifiAccessPoints_1				= wifiAccessPoints.createNestedObject();
		wifiAccessPoints_1["macAddress"]			= mac_address[1];
		wifiAccessPoints_1["signalStrength"]		= recep_power[1];
		wifiAccessPoints_0["signalToNoiseRatio"]    = 0;

		delay(1000);

		Serial.println("Filling Json with third wifi object...");
		Serial.println("macAdress : " + mac_address[2]);
		Serial.print("Strength	: ");
		Serial.println(recep_power[2]);
		
		JsonObject wifiAccessPoints_2				= wifiAccessPoints.createNestedObject();
		wifiAccessPoints_2["macAddress"]			= mac_address[2];
		wifiAccessPoints_2["signalStrength"]		= recep_power[2];
		wifiAccessPoints_0["signalToNoiseRatio"]    = 0;

		delay(1000);
		 
		String requestBody;
		serializeJson(req, requestBody);

		Serial.println("");
		Serial.print(requestBody);
		Serial.println("");
		 
		int httpResponseCode = http.POST(requestBody);

		while(true) {
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
				accuracy = accuracy / 50;
				
				return 0;
			} else {
				Serial.printf("Error occurred while sending HTTP POST");
				return -1;
			}
		}
	}

	return -1;
}

uint8_t* TrackChip::get_bssid(int a){
    uint8_t* ret = new uint8_t[TAILLE_ADRESSE_MAC];
    for(int i = 0; i <TAILLE_ADRESSE_MAC ;i++){
      ret[i] = bssidtab[a][i];
      Serial.print(ret[i]);
      Serial.print("-");
    }
    Serial.println("");
    return ret;
  }

String TrackChip::create_message1(){
  char temp[2];
  uint8_t* mac1_addr = this->get_bssid(0);
  int mac1_power = abs(recep_power[0]);
  int altitude = 23;//TrackChip::get_altitude();
  String res = "01";
  Serial.print("taille auth :");
  Serial.println(res.length());
  res+=String(mac1_power);
  /*for (int i = 0; i <TAILLE_ADRESSE_MAC;i++){
    Serial.print(mac1_addr[i]);
    sprintf(temp,"%2X",mac1_addr[i]);
    Serial.print(": ");
    Serial.println(temp);
    Wisol::complete_hexa_bytes(temp, 1);
    res += temp;
    }*/
   res+= TrackChip::part_bssid_to_hexa(mac1_addr);
   res+= String(altitude,HEX);
   res+="00";
   return res;
  }

String TrackChip::create_message2(){
  char temp[2];
  uint8_t* mac2_addr = this->get_bssid(1);
  int mac2_power = abs(recep_power[1]);
  String res = "02";
  res+= String(mac2_power);
  /*for (int i = 0; i <TAILLE_ADRESSE_MAC;i++){
    Serial.print(mac2_addr[i]);
    sprintf(temp,"%2X",mac2_addr[i]);
    Serial.print(": ");
    Serial.println(temp);
    res += temp;
    }*/
   res+= TrackChip::part_bssid_to_hexa(mac2_addr);
   res+="0000";
   return res;
  }

String TrackChip::create_message3(){
  int prec = 5;
  String res = "03";
  String trame = "$GPGGA,123519,4807.038,N,01131.324,E,1,08,0.9,545.4,M,46.9,M, , *42";//trackChip.get_position();
  int lat_angle, lat_minute; 
  double lat_seconde;
  char lat_c;
  int lng_angle,lng_minute;
  double lng_seconde;
  char lng_c;
  int altitude = 23;//TrackChip::get_altitude();
  res+=String(altitude,HEX);
  Wisol::trame_GPGGA_to_DMS(trame, &lat_angle, &lat_minute, &lat_seconde, &lat_c, &lng_angle, &lng_minute, &lng_seconde,  &lng_c);
  res+= Wisol::dms_lat_to_trame_hexa(lat_c, lat_angle, lat_minute, lat_seconde,prec);
  res+= Wisol::dms_lng_to_trame_hexa(lng_c, lng_angle, lng_minute, lng_seconde,prec);
  return res;
}

void TrackChip::chose_message_to_send(){
  String temp="";
  if(gps->receive_fix()) {
    temp = TrackChip::create_message3();
    Serial.println(temp);
    Wisol::send_string_data(temp);
  }
  else {
    temp=TrackChip::create_message1();
    Serial.println(temp);
    Wisol::send_string_data(temp);
    temp = TrackChip::create_message2();
    Serial.println(temp);
    Wisol::send_string_data(temp);
  }
}


//function used in create message
String TrackChip::part_bssid_to_hexa(uint8_t* macaddr){
    char temp[2];
    String res="";
    for (int i = 0; i <TAILLE_ADRESSE_MAC;i++){
      Serial.print(macaddr[i]);
      sprintf(temp,"%2X",macaddr[i]);
      Wisol::complete_hexa_bytes(res, 1);
      Serial.print(": ");
      Serial.println(temp);
      res+=temp;
    }
    return res;
}
