EESchema Schematic File Version 4
LIBS:version_sigfox-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
NoConn ~ 5500 3750
NoConn ~ 4400 3150
NoConn ~ 4400 3250
NoConn ~ 4400 3350
NoConn ~ 4400 3450
NoConn ~ 4400 3550
NoConn ~ 4400 3650
NoConn ~ 4400 3750
NoConn ~ 4400 3850
NoConn ~ 4400 3950
NoConn ~ 4400 4050
NoConn ~ 4400 4150
NoConn ~ 4400 4250
NoConn ~ 4400 4350
NoConn ~ 4400 4450
NoConn ~ 5500 3850
Text GLabel 5500 3450 2    50   Input ~ 0
GPS_TX0
Text GLabel 5500 3550 2    50   Input ~ 0
SDA
Text GLabel 5500 4450 2    50   Input ~ 0
GND
NoConn ~ 5500 3150
Text GLabel 4700 2550 3    50   Input ~ 0
3V3
Text GLabel 4800 2550 3    50   Input ~ 0
3V3
Text GLabel 4900 2550 3    50   Input ~ 0
GND
Text GLabel 5100 2550 3    50   Input ~ 0
SDA
$Comp
L track_chip:GPS_PA6H U3
U 1 1 60213494
P 6600 2050
F 0 "U3" H 6942 1035 50  0000 C CNN
F 1 "GPS_PA6H" H 6942 1126 50  0000 C CNN
F 2 "track_chip:GPS_PA6H" H 6600 2050 50  0001 C CNN
F 3 "" H 6600 2050 50  0001 C CNN
	1    6600 2050
	1    0    0    -1  
$EndComp
NoConn ~ 6500 2850
Text GLabel 6500 2750 0    50   Input ~ 0
3V3
Text GLabel 6500 2650 0    50   Input ~ 0
GND
Text GLabel 6500 2450 0    50   Input ~ 0
GPS_TX0
NoConn ~ 6500 2050
NoConn ~ 6500 2250
Text GLabel 5150 4950 2    50   Input ~ 0
VBAT
Text GLabel 5150 4800 2    50   Input ~ 0
GND
$Comp
L track_chip:charger_mr010 U7
U 1 1 60216DFB
P 5250 5150
F 0 "U7" V 5438 4372 50  0000 R CNN
F 1 "charger_mr010" V 5347 4372 50  0000 R CNN
F 2 "track_chip:charger_mr010" H 5250 5150 50  0001 C CNN
F 3 "" H 5250 5150 50  0001 C CNN
	1    5250 5150
	0    1    1    0   
$EndComp
Wire Wire Line
	5150 5050 5150 4950
Wire Wire Line
	5050 5050 5050 4800
Wire Wire Line
	5050 4800 5150 4800
$Comp
L track_chip:esp32_NodeMCU U2
U 1 1 6021AB3C
P 4500 3150
F 0 "U2" H 4950 3415 50  0000 C CNN
F 1 "esp32_NodeMCU-track_chip" H 4950 3324 50  0000 C CNN
F 2 "track_chip:esp32" H 4950 3300 50  0001 C CNN
F 3 "" H 4950 3300 50  0001 C CNN
	1    4500 3150
	1    0    0    -1  
$EndComp
$Comp
L track_chip:bmp180 U4
U 1 1 6021BEE0
P 4700 2450
F 0 "U4" H 5278 2296 50  0000 L CNN
F 1 "bmp180-track_chip" H 5278 2205 50  0000 L CNN
F 2 "track_chip:bmp180" H 5000 2650 50  0001 C CNN
F 3 "" H 5000 2650 50  0001 C CNN
	1    4700 2450
	0    -1   -1   0   
$EndComp
Text GLabel 5500 3250 2    50   Input ~ 0
SCL
Text GLabel 5000 2550 3    50   Input ~ 0
SCL
Text GLabel 6500 2150 0    50   Input ~ 0
EN_GPS
NoConn ~ 6500 2350
Text GLabel 5500 3650 2    50   Input ~ 0
EN_GPS
NoConn ~ 5500 4350
Text GLabel 5500 4550 2    50   Input ~ 0
3V3
Text GLabel 6450 4350 0    50   Input ~ 0
3V3
Text GLabel 6450 4450 0    50   Input ~ 0
GND
Text GLabel 6450 4250 0    50   Input ~ 0
RST_WSL
Text GLabel 5500 4250 2    50   Input ~ 0
RST_WSL
NoConn ~ 6500 2550
$Comp
L track_chip:polulu U1
U 1 1 602554CA
P 6650 5100
F 0 "U1" H 7328 5001 50  0000 L CNN
F 1 "polulu" H 7328 4910 50  0000 L CNN
F 2 "track_chip:polulu" H 6650 5100 50  0001 C CNN
F 3 "" H 6650 5100 50  0001 C CNN
	1    6650 5100
	1    0    0    -1  
$EndComp
NoConn ~ 6550 5100
Text GLabel 6550 5200 0    50   Input ~ 0
VBAT
Text GLabel 6550 5300 0    50   Input ~ 0
GND
Text GLabel 6550 5400 0    50   Input ~ 0
5V
Text GLabel 4400 4550 0    50   Input ~ 0
5V
NoConn ~ 5500 4150
NoConn ~ 5500 3350
NoConn ~ 6450 3950
NoConn ~ 6450 4050
Text GLabel 5500 3950 2    50   Input ~ 0
MCU_TX2
Text GLabel 6450 3850 0    50   Input ~ 0
MCU_TX2
NoConn ~ 5500 4050
NoConn ~ 6450 3750
$Comp
L track_chip:brkws01 wisol1
U 1 1 602BF8D9
P 7450 3450
F 0 "wisol1" V 8004 3578 50  0000 L CNN
F 1 "brkws01" V 8095 3578 50  0000 L CNN
F 2 "track_chip:BRWS01" H 7450 3450 50  0001 C CNN
F 3 "" H 7450 3450 50  0001 C CNN
	1    7450 3450
	0    1    1    0   
$EndComp
$EndSCHEMATC
