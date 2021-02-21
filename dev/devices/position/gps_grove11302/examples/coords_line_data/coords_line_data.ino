#include <GROVE11302.h>

GROVE11302 gps_grove = GROVE11302();

bool receivefix(String trame);

void setup()
{
  Serial.begin(115200);                         // the Serial port of Arduino baud rate => Communication between ESP and computer via USB port.
}
 
void loop()
{  
  gps_grove.get_data_line();

  Serial.print("\n=============\n");
  Serial.print("buffer : "); 
  Serial.write(gps_grove.buffer, 70);
  Serial.print("\n=============\n");
  char* buf = (char*) gps_grove.buffer;
  String trame = String(buf);
  Serial.print("trame : "); 
  Serial.println(trame);

  Serial.print("Ai-je reçu un fix : "); 
  Serial.println(receive_fix(trame));
  delay(1000);
  trame = "$GPGGA,123519,4807.038,N,01131.324,E,1,08,0.9,545.4,M,46.9,M, , *42";
  Serial.print("trame : "); 
  Serial.println(trame);
  Serial.print("Ai-je reçu un fix : "); 
  Serial.println(receive_fix(trame));
  delay(5000);
}

bool receive_fix(String trame){
  int MIN_SIZE_CHAR_TRAME = 67;
  Serial.print("trame length: "); 
  Serial.println(trame.length());
  return trame.length() >=MIN_SIZE_CHAR_TRAME;
  }
