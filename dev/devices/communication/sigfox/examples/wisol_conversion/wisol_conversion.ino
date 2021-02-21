#include "Wisol.h"
String retour;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("end setup");
}

void loop() {
  Wisol w;
  char cardinal_lat = 'N';
  int angle_lat = 48;
  int minute_lat = 20;
  double seconde_lat = 43.051;

  char cardinal_lng = 'E';
  int angle_lng = 2;
  int minute_lng = 21;
  double seconde_lng = 26.629;

  int altitude = 46;
  
  int prec = 5;
  Serial.println("Test fonction conversion");
  String res;
  res = w.dms_lat_to_trame_hexa(cardinal_lat, angle_lat, minute_lat, seconde_lat,prec);
  res+= w.dms_lng_to_trame_hexa(cardinal_lng, angle_lng, minute_lng, seconde_lng, prec);
  res+= w.altitude_to_trame_hexa(altitude);
  w.send_string_data(res);//sending int
  
  // put your main code here, to run repeatedly:
     while (Serial2.available()>0) {
    retour = Serial2.readStringUntil('\n');
    Serial.println(retour);
  }
  while(1);
}
