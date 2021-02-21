#include "Wisol.h"

String retour;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wisol w;
  //w.send_string_data("004A882F000398DC2E");// latitude, longitude, altitude int
  //w.send_string_data("2E4243618E4016DFA4"); // altitude, latitude, longitude en float
  w.send_string_data("2E02e971f200242520"); // altitude, latitude, longitude en int
}

void loop() {
	  Serial.println("Entering loop");
  // put your main code here, to run repeatedly:
     while (Serial2.available()>0) {
    retour = Serial2.readStringUntil('\n');
    Serial.println(retour);
  }
  while(1);
}
