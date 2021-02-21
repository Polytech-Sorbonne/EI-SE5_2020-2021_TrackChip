#ifndef WIFI_SCANNER_H
#define WIFI_SCANNER_H

#include <stdlib.h>
#include <string.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Eugeune's mobile network
char *AP_SSID = "Redmi";
char *AP_PWD = "toto1234";

const char  *serverAddress = "https://www.googleapis.com/geolocation/v1/geolocate?key=AIzaSyDMnY8W47H_ztdC4sJjo2Z9_bu2y9-zEPM";
int          port = 8080;

String 	mac_address[3];
int 	recep_power[3];

double location_lat  = 0.000000;
double location_lng  = 0.000000;
long   accuracy      = 0;

void init();

int postDataToServer();

void wifi_scan();

#endif