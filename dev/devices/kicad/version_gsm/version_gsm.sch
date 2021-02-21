EESchema Schematic File Version 4
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
Text GLabel 5500 3350 2    50   Input ~ 0
TX0
Text GLabel 5500 3550 2    50   Input ~ 0
SDA
Text GLabel 5500 3950 2    50   Input ~ 0
TX2
Text GLabel 5500 4050 2    50   Input ~ 0
RX2
Text GLabel 5500 4450 2    50   Input ~ 0
GND
NoConn ~ 5500 3150
Text GLabel 6750 3100 0    50   Input ~ 0
3.3V
Text GLabel 6750 3200 0    50   Input ~ 0
3.3V
Text GLabel 6750 3300 0    50   Input ~ 0
GND
Text GLabel 6750 3500 0    50   Input ~ 0
SDA
$Comp
L track_chip:GPS_PA6H U3
U 1 1 60213494
P 6750 3750
F 0 "U3" H 7092 2735 50  0000 C CNN
F 1 "GPS_PA6H" H 7092 2826 50  0000 C CNN
F 2 "track_chip:GPS_PA6H" H 6750 3750 50  0001 C CNN
F 3 "" H 6750 3750 50  0001 C CNN
	1    6750 3750
	1    0    0    -1  
$EndComp
NoConn ~ 6650 4550
Text GLabel 6650 4450 0    50   Input ~ 0
3.3V
Text GLabel 6650 4350 0    50   Input ~ 0
GND
Text GLabel 6650 4150 0    50   Input ~ 0
TX0
NoConn ~ 6650 3750
NoConn ~ 6650 3950
$Comp
L track_chip:SIM800L U1
U 1 1 60218FF3
P 3250 3900
F 0 "U1" H 3978 3701 50  0000 L CNN
F 1 "SIM800L" H 3978 3610 50  0000 L CNN
F 2 "track_chip:SIM800L" H 3250 3900 50  0001 C CNN
F 3 "" H 3250 3900 50  0001 C CNN
	1    3250 3900
	1    0    0    -1  
$EndComp
Text GLabel 3150 4300 0    50   Input ~ 0
TX2
NoConn ~ 3150 4100
NoConn ~ 3150 3900
$Comp
L Device:D D1
U 1 1 6021D78B
P 2650 3850
F 0 "D1" V 2650 3950 50  0000 C CNN
F 1 "0.8V" V 2650 3725 50  0000 C CNN
F 2 "Diode_THT:D_DO-15_P10.16mm_Horizontal" H 2650 3850 50  0001 C CNN
F 3 "~" H 2650 3850 50  0001 C CNN
	1    2650 3850
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C1
U 1 1 6021E3B7
P 2650 4350
F 0 "C1" H 2400 4450 50  0000 L CNN
F 1 "100u" H 2350 4250 50  0000 L CNN
F 2 "Capacitor_THT:CP_Axial_L10.0mm_D4.5mm_P15.00mm_Horizontal" H 2688 4200 50  0001 C CNN
F 3 "~" H 2650 4350 50  0001 C CNN
	1    2650 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 4000 2650 4200
$Comp
L track_chip:Earth #PWR0103
U 1 1 6021F058
P 2650 4750
F 0 "#PWR0103" H 2650 4500 50  0001 C CNN
F 1 "Earth" H 2650 4600 50  0001 C CNN
F 2 "" H 2650 4750 50  0001 C CNN
F 3 "~" H 2650 4750 50  0001 C CNN
	1    2650 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 4500 2650 4600
Wire Wire Line
	2650 4000 3150 4000
Wire Wire Line
	3150 4400 3150 4600
Wire Wire Line
	3150 4600 2650 4600
Connection ~ 2650 4600
Wire Wire Line
	2650 4600 2650 4750
Text GLabel 2500 4600 0    50   Input ~ 0
GND
Text GLabel 4800 2300 0    50   Input ~ 0
VBAT
Text GLabel 4800 2450 0    50   Input ~ 0
GND
$Comp
L track_chip:charger_mr010 U7
U 1 1 60216DFB
P 4700 2100
F 0 "U7" V 4888 1322 50  0000 R CNN
F 1 "charger_mr010" V 4797 1322 50  0000 R CNN
F 2 "track_chip:charger_mr010" H 4700 2100 50  0001 C CNN
F 3 "" H 4700 2100 50  0001 C CNN
	1    4700 2100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4800 2200 4800 2300
Wire Wire Line
	4900 2200 4900 2450
Wire Wire Line
	4900 2450 4800 2450
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
P 6850 3100
F 0 "U4" H 7428 2946 50  0000 L CNN
F 1 "bmp180-track_chip" H 7428 2855 50  0000 L CNN
F 2 "track_chip:bmp180" H 7150 3300 50  0001 C CNN
F 3 "" H 7150 3300 50  0001 C CNN
	1    6850 3100
	1    0    0    -1  
$EndComp
Text GLabel 5500 3250 2    50   Input ~ 0
SCL
Text GLabel 6750 3400 0    50   Input ~ 0
SCL
Text GLabel 6650 3850 0    50   Input ~ 0
EN_GPS
NoConn ~ 6650 4050
$Comp
L track_chip:polulu U5
U 1 1 6021A9B1
P 3300 2950
F 0 "U5" H 3978 2851 50  0000 L CNN
F 1 "polulu" H 3978 2760 50  0000 L CNN
F 2 "track_chip:polulu" H 3300 2950 50  0001 C CNN
F 3 "" H 3300 2950 50  0001 C CNN
	1    3300 2950
	1    0    0    -1  
$EndComp
Text GLabel 3200 3150 0    50   Input ~ 0
GND
NoConn ~ 3200 2950
Text GLabel 3200 3050 0    50   Input ~ 0
VBAT
Connection ~ 2650 4000
NoConn ~ 5500 3650
Text GLabel 5500 3750 2    50   Input ~ 0
EN_GPS
NoConn ~ 5500 4250
NoConn ~ 5500 4350
Text GLabel 3150 4200 0    50   Input ~ 0
RX2
Text GLabel 4400 4550 0    50   Input ~ 0
5V
Text GLabel 5500 4550 2    50   Input ~ 0
3.3V
Text GLabel 3200 3250 0    50   Input ~ 0
5V
Text GLabel 2650 3550 1    50   Input ~ 0
5V
Wire Wire Line
	2650 3700 2650 3550
NoConn ~ 5500 3450
NoConn ~ 6650 4250
Wire Wire Line
	2500 4600 2650 4600
NoConn ~ 5500 4150
$EndSCHEMATC
