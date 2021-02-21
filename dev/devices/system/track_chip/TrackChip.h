#ifndef TRACK_CHIP_H
#define TRACK_CHIP_H

#include <stdlib.h>
#include <string.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Arduino.h>

#include <BMP180I2C.h>
#include "GROVE11302.h"
#include <Wisol.h>
#define TAILLE_ADRESSE_MAC 6
#define NB_ADRESSE_MAC 2
//typedef uint8_t struct_bssid[TAILLE_ADRESSE_MAC];
//typedef struct_bssid struct_bssid_tab[NB_ADRESSE_MAC];
class TrackChip {

private :
	GROVE11302 * gps; 

	// Wifi ID
	char * AP_SSID	= "Redmi";
	char * AP_PWD 	= "toto1234";

	// api constexpr_ID 
	char * serverAddress = "https://www.googleapis.com/geolocation/v1/geolocate?key=AIzaSyDMnY8W47H_ztdC4sJjo2Z9_bu2y9-zEPM";
	int port = 8080;

	// Wifi scanner var
	String mac_address[3];
	int recep_power[3];
	float location_lat  	= 0;
	float location_lng  	= 0;
	int accuracy			= 0;
	
	//Mac address
	uint8_t bssidtab[NB_ADRESSE_MAC][TAILLE_ADRESSE_MAC];
	
public :
	TrackChip();
	~TrackChip();

	// Peripherals utilities
	void send_data(String s);	// Wisol
	float get_altitude();		// Altimètre
	String get_position();		// GSP

	// Wifi utilities
	void connect_to_wifi();		// Se connecte au wifi	
	void wifi_scan();		// scan les réseaux wifi sans avoir besoin d'y être connecté 
	int send_mac_and_get_pos();	// 

	// Wifi Getters
	int get_wifi_accuracy()	{ return accuracy;	}
	float get_wifi_lat()	{ return location_lat;	}
	float get_wifi_lng()	{ return location_lng;	}
  uint8_t*  get_bssid(int i);

  //create different message
   String create_message1();
   String create_message2();
   String create_message3();
   void chose_message_to_send();

   //function used in create message
   String part_bssid_to_hexa(uint8_t* macaddr);
};

#endif
