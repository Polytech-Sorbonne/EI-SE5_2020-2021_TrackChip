#include "Wisol.h"
void setup() {
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  char lat_c,lng_c;
  int lat_minute, lat_angle;
  double lat_seconde;
  int lng_minute, lng_angle;
  double lng_seconde;
  
 Wisol w;
 String trame = "$GPGGA,064036.289,4836.5375,N,00740.9373,E,1,04,3.2,200.2,M,,,,0000*0E";
 w.trame_GPGGA_to_DMS(trame, &lat_angle, &lat_minute, &lat_seconde, &lat_c, &lng_angle, &lng_minute, &lng_seconde, &lng_c);
  Serial.println("lat : ");
  Serial.println(lat_angle);
  Serial.println(lat_minute);
  Serial.println(lat_seconde);
  Serial.println(lat_c);
  Serial.println("lng : ");
  Serial.println(lng_angle);
  Serial.println(lng_minute);
  Serial.println(lng_seconde);
  Serial.println(lng_c);
  int altitude = 24;
  //Test_send_trame
  Serial.println("test DMS_to_dd");
  double lat = w.Dms_to_dd(lat_c,lat_angle,lat_minute, lat_seconde);
  Serial.println(lat);
  double lng = w.Dms_to_dd(lng_c,lng_angle,lng_minute, lng_seconde);
  Serial.println(lng);
  Serial.println("---------");
  int prec = 5;
  double a = w.shift_latitude(lat);
  Serial.println(a);
  int temp = w.double_to_int(a, prec);
  Serial.println(temp);
  Serial.println("Test_send_trame :");
  String res;
  res = w.altitude_to_trame_hexa(altitude);
  Serial.println(res);
  
  res+= w.dms_lat_to_trame_hexa(lat_c, lat_angle, lat_minute, lat_seconde,prec);
  Serial.println(res);
  
  res+= w.dms_lng_to_trame_hexa(lng_c, lng_angle, lng_minute, lng_seconde, prec);
  Serial.println(res);
  //w.send_string_data(res);//sending int
  w.send_trame(lat_angle, lat_minute, lat_seconde, lat_c, lng_angle, lng_minute, lng_seconde, lng_c, altitude);
  while(1);
}
