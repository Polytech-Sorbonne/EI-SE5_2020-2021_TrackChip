void setup()
{
    Serial.begin(115200);                       // the Serial port of Arduino baud rate => Communication between ESP and computer via USB port.
    Serial2.begin(9600);                        // Hardware Serial Port 2 => Communication between ESP and GPS
}
 
void loop()
{  
  while (Serial2.available()) {
    Serial.print(char(Serial2.read()));
    delay(200);
  }
}
