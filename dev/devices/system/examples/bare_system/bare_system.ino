#include "bare_system.h"

String   mac_address[NB_ADRESSE_MAC];
int      recep_power[NB_ADRESSE_MAC];

uint8_t mac_int[TAILLE_ADRESSE_MAC];

uint8_t bssidtab[NB_ADRESSE_MAC][TAILLE_ADRESSE_MAC];

Wisol w = Wisol();
BMP180I2C bmp = BMP180I2C(BMP_I2C_ADDRESS); 
GROVE11302 gps = GROVE11302();

void setup() {
	Serial.begin(115200); 

	WiFi.mode(WIFI_STA);
	WiFi.disconnect();
	delay(100);
										
	Wire.begin();   
	bmp.init();
}

void loop() {
	chose_message_to_send();
	delay(1000*60*5);
}

void chose_message_to_send() {
	String temp;
	if(receive_fix()) {
		temp = create_message3();
		Wisol::send_string_data(temp);
	} 
	else {
		wifi_scan();

		temp = create_message1();
		temp = Wisol::complete_hexa_bytes(temp, 10);
		Wisol::send_string_data(temp);


		temp = create_message2();
		temp = Wisol::complete_hexa_bytes(temp, 10); 

		delay(1000*30);
		Wisol::send_string_data(temp);
	}
}

void get_bssid(int a) {
	for(int i = 0; i < TAILLE_ADRESSE_MAC ;i++) {
		mac_int[i] = bssidtab[a][i];
	}
}

String create_message1(){
	char temp[2];
	get_bssid(0);
	uint8_t* mac1_addr = mac_int;

	int mac1_power = (-1) * recep_power[0];
	Serial.print("mac1_power : ");
	Serial.println(mac1_power);

	int altitude = (int)(bmp.computeAltitude());
	Serial.print("altitude : ");
	Serial.println(altitude);

	String res = "";

	//AUTH
	String auth = "01";
	res += auth;

	//PUISSANCE
	res+= String(mac1_power, HEX);

	//MAC
	for (int i = 0; i <TAILLE_ADRESSE_MAC;i++){
		sprintf(temp,"%X",mac1_addr[i]);
		String tmp = String(temp);
		res += Wisol::complete_hexa_bytes(tmp, 1);
	}

	// ALTITUDE
	res+= String(altitude, HEX);
	return res;
}

String create_message2(){
	char temp[2];
	get_bssid(1);
	uint8_t* mac2_addr = mac_int;
	int mac2_power = (-1) * recep_power[1];
	int altitude = (int)(bmp.computeAltitude());
	String res = "";

	//AUTH
	String auth = "02";
	res += auth;

	//PUISSANCE
	res+= String(mac2_power, HEX);

	//MAC
	for (int i = 0; i <TAILLE_ADRESSE_MAC;i++){
		sprintf(temp,"%X",mac2_addr[i]);
		String tmp = String(temp);
		res += Wisol::complete_hexa_bytes(tmp, 1);
	}

	//ALTITUDE
	res+= String(altitude, HEX);
	return res;
}

String create_message3(){
	int prec = 5;
	String res; 
	String trame = "$GPGGA,123519,4807.038,N,01131.324,E,1,08,0.9,545.4,M,46.9,M, , *42";//trackChip.get_position();
	int lat_angle, lat_minute; 
	double lat_seconde;
	char lat_c;
	int lng_angle,lng_minute;
	double lng_seconde;
	char lng_c;
	int altitude = bmp.computeAltitude();


	//AUTH
	String auth = "03";
	res += auth;

	//ALTITUDE
	res+=String(altitude, HEX);

	//POSITION
	Wisol::trame_GPGGA_to_DMS(trame, &lat_angle, &lat_minute, &lat_seconde, &lat_c, &lng_angle, &lng_minute, &lng_seconde,  &lng_c);
	res+= Wisol::dms_lat_to_trame_hexa(lat_c, lat_angle, lat_minute, lat_seconde, prec);
	res+= Wisol::dms_lng_to_trame_hexa(lng_c, lng_angle, lng_minute, lng_seconde, prec);

	res = Wisol::complete_hexa_bytes(res, 10);
	return res;
}

void wifi_scan() {    
	int wifi_saved = 0;

	uint8_t *bssid;
	char bssid_str[18];
	int power;

	int n = WiFi.scanNetworks();

	if (n == 0) {
		Serial.println("no networks found");
	}
	else {
		for (int i = 0; i < n; ++i) {
			bssid = WiFi.BSSID(i);
			sprintf(bssid_str, "%X-%X-%X-%X-%X-%X",bssid[5], bssid[4], bssid[3], bssid[2], bssid[1], bssid[0]); 

			power = int(WiFi.RSSI(i));

			// select fix WiFi which are in google database
			if(bssid_str[9] == 'B' && bssid_str[10] == 'D' && wifi_saved < NB_ADRESSE_MAC){
				for(int i = 0; i < TAILLE_ADRESSE_MAC ;i++){
					bssidtab[wifi_saved][i] = bssid[i];
				}

				recep_power[wifi_saved] = power;
				wifi_saved++;
			}
			delay(10);
		}
		// Wait for 1s before scanning again
		delay(1000);
	}
}

bool receive_fix() {
	//GROVE11302 gps_grove = GROVE11302();
	gps.get_data_line();
	char* buf = (char*) gps.buffer;
	String trame = String(buf);
	int MIN_SIZE_CHAR_TRAME = 67;
	return trame.length() >=MIN_SIZE_CHAR_TRAME;
}
