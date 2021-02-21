/*
Librairie permettant d'envoyer une chaine de caractère de 12 octets d'un ESP32 vers un module Sigfox Wisol
*/
#include "Wisol.h"

//Constructor
Wisol::Wisol(int baudrate, int RX, int TX){
	Serial2.begin(baudrate, SERIAL_8N1, RX, TX);
	while (!Serial2);
}

Wisol::Wisol(){
	Wisol(9600, RX2, TX2);
}

//private function
bool Wisol::IsHexCharOrNewLine(char c){
	return (c >= '0' && c <= '9') ||
		(c >= 'A' && c <= 'F') ||
		(c >= 'a' && c <= 'f') ||
		c == '\n'; // You may want to test for \r as well
}

bool Wisol::IsHex(char* text){
	bool temp = true;
	for (int i = 0; i < strlen(text); i++){
		temp = temp && IsHexCharOrNewLine(text[i]);
	}
	return temp;
}

bool Wisol::string_ok(String verif){
	//verifier que la string fait moins de 12 octets
	int n = verif.length() ;
	if (n > 24) {
		Serial.println("string too long");
		return false;
	}
	char char_array[n + 1];
	strcpy(char_array, verif.c_str());
	//qu'elle ne contient que des caractères Hexa
	return IsHex(char_array);
}

//public function
void Wisol::send_string_data(String envoie) {

	Serial.println("Wisol::send_string_data => envoie = " );
	Serial.println(envoie);

 	if (string_ok(envoie)) {
		Serial.println("Wisol::send_string_data => string is valid" );
		String command = "AT$SF=";

		command = command + envoie;
		Serial.print("Wisol::send_string_data => sending : " );
		Serial.println(command);
		Serial2.println(command);

	} else {
		Serial.println("Wisol::send_string_data => string is not valid" );

	}
}

String Wisol::double_to_hexa(double a, int prec){
	String message = "";
	int temp;
	temp = double_to_int(a, prec);
	message = int_to_hexa(temp);
	return message;
}

String Wisol::int_to_hexa(int a){
	char hex_string[20];
	sprintf(hex_string, "%X", a); //convert number to hex
	return hex_string;
}


int Wisol::double_to_int(double a, int prec){
	int res = round(a*pow (10, prec));
	return res;
}


// convertis aussi bien la latitude que la longitude. Cette fonction suppose que le paramètre cardinal est N, S, E ou O.
double Wisol::Dms_to_dd(char cardinal, int angle, int minute, double seconde){
	double res = angle;
	double temp = seconde/60;
	res += (minute+temp)/60;

	if ( cardinal == 'S' || cardinal == 'O') {
		res = -res;
	}

	return res;
}

double Wisol::shift_latitude(double lat){
	return lat+180;
}

double Wisol::shift_longitude(double lng){
	return lng+90;
}

String Wisol::complete_hexa_bytes(String hexa, int nb_bytes){ // prend en argument une chaine hexa et le nombre d'octets voulu pour le callback et complete avec des 0 big edians
	int add = 2*nb_bytes - hexa.length();
	String complete = "";
	for(int i = 0; i<add;i++){
		complete = complete+"0";
	}
	return complete +hexa;
}

String Wisol::dms_lat_to_trame_hexa(char cardinal, int angle, int minute, double seconde,int prec){
	double dd = shift_latitude(Dms_to_dd(cardinal, angle, minute, seconde));
	String res_lat = Wisol::double_to_hexa(dd, prec);
	res_lat = complete_hexa_bytes(res_lat, 4);
	return res_lat;
}

String Wisol::dms_lng_to_trame_hexa(char cardinal, int angle, int minute, double seconde,int prec){
	double dd = shift_longitude(Dms_to_dd(cardinal, angle, minute, seconde));
	String res_lat = Wisol::double_to_hexa(dd, prec);
	res_lat = complete_hexa_bytes(res_lat,4);
	return res_lat;
}

String Wisol::altitude_to_trame_hexa(int altitude){
	String res_alt = Wisol::int_to_hexa(altitude);
	return complete_hexa_bytes(res_alt, 1);
}


void Wisol::send_trame(int lat_angle, int lat_minute, double lat_seconde, char lat_c, int lng_angle, int lng_minute, double lng_seconde, char lng_c, int altitude){
	int prec = 5;
  String res;
	res= Wisol::altitude_to_trame_hexa(altitude);
  res += Wisol::dms_lat_to_trame_hexa(lat_c, lat_angle, lat_minute, lat_seconde,prec);
  res+= Wisol::dms_lng_to_trame_hexa(lng_c, lng_angle, lng_minute, lng_seconde, prec);
  Wisol::send_string_data(res);//sending int
}

//parse trame GPS
bool  Wisol::verif_type(String trame){
    return (trame.indexOf("$GPGGA") == 0);
  }

void Wisol::GPGGA_to_DMS(String test, int* angle, int* minute, double* seconde){
  //séparer la partie entière de la partie décimale :
  String angle_minute = test.substring(0, test.indexOf('.'));
  test.remove(0, test.indexOf('.')+1);

  //séparer les angles et les minutes
  int n  = angle_minute.length();
  String s_minute = angle_minute.substring(n-2,n);
  *minute = s_minute.toInt();
  angle_minute.remove(n-2,n);
  *angle = angle_minute.toInt();
  //convertir les secondes
  int temp = test.toDouble();
  *seconde =  (double) (temp*60/100)/100;
  }


void Wisol::trame_GPGGA_to_DMS(String trame, int *lat_angle, int *lat_minute, double *lat_seconde, char* lat_c, int *lng_angle, int *lng_minute, double *lng_seconde, char* lng_c){
if( Wisol::verif_type(trame)) {
  char delimiter = ',';
  int param_suppr = 0;
  String test;
  char buf[20];
  while(param_suppr <=6){
    test = trame.substring(0, trame.indexOf(delimiter));
    if(param_suppr == 2){
      Wisol::GPGGA_to_DMS(test, lat_angle, lat_minute, lat_seconde);
      }
    else if( param_suppr == 4){
      Wisol::GPGGA_to_DMS(test, lng_angle, lng_minute, lng_seconde);
      }
    else if(param_suppr == 3){
      test.toCharArray(buf,20);
     *lat_c = buf[0];
      }
    else if (param_suppr == 5){
      test.toCharArray(buf,20);
      *lng_c = buf[0];
      }
    trame.remove(0, trame.indexOf(delimiter)+1);
    param_suppr+=1;
  }
}
}
