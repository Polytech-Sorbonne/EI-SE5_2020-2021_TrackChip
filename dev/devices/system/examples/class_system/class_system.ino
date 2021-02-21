#include "TrackChip.h"

String position, message;
float lat, lng, altitude;
int prc;

TrackChip trackChip = TrackChip();

void setup() {

	Serial.begin(115200); 
	while (!Serial); 
}

void loop() {
  
	//altitude = trackChip.get_altitude();
	//position = trackChip.get_position();

	Serial.println("========");
	Serial.print("altitude : "); Serial.print(altitude); Serial.println("m");
	Serial.print("position : "); Serial.println(position);
	/*Serial.print("res : ");
	String res = trackChip.create_message1();
	Serial.println(res);
	Serial.print("Taille message 1 : ");
	Serial.println(res.length());
	res = trackChip.create_message2();
	Serial.println(res);
	Serial.print("Taille message 2 : ");
	Serial.println(res.length());
	res = trackChip.create_message3();
	Serial.println(res);
	Serial.print("Taille message 3 : ");
	Serial.println(res.length());*/
	trackChip.chose_message_to_send();

	while(1);
		delay(1000*60*1);
}
