#include <stdlib.h>
#include <string.h>
#include <WiFi.h>
#include <SPI.h>
#include <ArduinoJson.h>
#include <Arduino.h>

#include <BMP180I2C.h>
#include "GROVE11302.h"
#include <Wisol.h>

#define NB_ADRESSE_MAC 2
#define TAILLE_ADRESSE_MAC 6


void get_bssid(int a);
String create_message1();
String create_message2();
String create_message3();
void chose_message_to_send();
void wifi_scan();
bool receive_fix();
