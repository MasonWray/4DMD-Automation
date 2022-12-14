EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A 11000 8500
encoding utf-8
Sheet 1 1
Title "Hinge Tester Controller"
Date "2022-11-01"
Rev "0.1.0"
Comp "MobileDemand"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:+5V #PWR0101
U 1 1 6361D18B
P 5700 1600
F 0 "#PWR0101" H 5700 1450 50  0001 C CNN
F 1 "+5V" H 5715 1773 50  0000 C CNN
F 2 "" H 5700 1600 50  0001 C CNN
F 3 "" H 5700 1600 50  0001 C CNN
	1    5700 1600
	1    0    0    -1  
$EndComp
$Comp
L power:+24V #PWR0102
U 1 1 6361D49F
P 2750 4550
F 0 "#PWR0102" H 2750 4400 50  0001 C CNN
F 1 "+24V" H 2765 4723 50  0000 C CNN
F 2 "" H 2750 4550 50  0001 C CNN
F 3 "" H 2750 4550 50  0001 C CNN
	1    2750 4550
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 6361DBF4
P 8250 3650
F 0 "#PWR0103" H 8250 3400 50  0001 C CNN
F 1 "GND" H 8255 3477 50  0000 C CNN
F 2 "" H 8250 3650 50  0001 C CNN
F 3 "" H 8250 3650 50  0001 C CNN
	1    8250 3650
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x02_Female J3
U 1 1 6361FE6E
P 6000 1700
F 0 "J3" H 6028 1676 50  0000 L CNN
F 1 "Conn_01x02_Female" H 6028 1585 50  0000 L CNN
F 2 "TerminalBlock_TE-Connectivity:TerminalBlock_TE_282834-2_1x02_P2.54mm_Horizontal" H 6000 1700 50  0001 C CNN
F 3 "~" H 6000 1700 50  0001 C CNN
	1    6000 1700
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Female J1
U 1 1 6362003C
P 2650 4100
F 0 "J1" H 2678 4076 50  0000 L CNN
F 1 "Conn_01x04_Female" H 2678 3985 50  0000 L CNN
F 2 "TerminalBlock_RND:TerminalBlock_RND_205-00234_1x04_P5.08mm_Horizontal" H 2650 4100 50  0001 C CNN
F 3 "~" H 2650 4100 50  0001 C CNN
	1    2650 4100
	-1   0    0    1   
$EndComp
$Comp
L Breakouts:TB67S128FTG U1
U 1 1 63628E93
P 3700 2900
F 0 "U1" H 3675 361 50  0000 C CNN
F 1 "TB67S128FTG" H 3675 270 50  0000 C CNN
F 2 "Modules:TB67S128FTG" H 3700 2950 50  0001 C CNN
F 3 "" H 3700 2950 50  0001 C CNN
	1    3700 2900
	1    0    0    -1  
$EndComp
$Comp
L power:+24V #PWR0104
U 1 1 6362E7A2
P 4100 1600
F 0 "#PWR0104" H 4100 1450 50  0001 C CNN
F 1 "+24V" H 4115 1773 50  0000 C CNN
F 2 "" H 4100 1600 50  0001 C CNN
F 3 "" H 4100 1600 50  0001 C CNN
	1    4100 1600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 6362F794
P 2850 4350
F 0 "#PWR0105" H 2850 4100 50  0001 C CNN
F 1 "GND" H 2855 4177 50  0000 C CNN
F 2 "" H 2850 4350 50  0001 C CNN
F 3 "" H 2850 4350 50  0001 C CNN
	1    2850 4350
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 63630014
P 4500 4900
F 0 "#PWR0106" H 4500 4650 50  0001 C CNN
F 1 "GND" H 4505 4727 50  0000 C CNN
F 2 "" H 4500 4900 50  0001 C CNN
F 3 "" H 4500 4900 50  0001 C CNN
	1    4500 4900
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 63630C1A
P 4100 1900
F 0 "#PWR0107" H 4100 1650 50  0001 C CNN
F 1 "GND" H 4105 1727 50  0000 C CNN
F 2 "" H 4100 1900 50  0001 C CNN
F 3 "" H 4100 1900 50  0001 C CNN
	1    4100 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 4900 4500 4900
Wire Wire Line
	2950 4500 2900 4500
Wire Wire Line
	2900 4500 2900 4550
Wire Wire Line
	2900 4600 2950 4600
Wire Wire Line
	2900 4550 2750 4550
Connection ~ 2900 4550
Wire Wire Line
	2900 4550 2900 4600
Wire Wire Line
	2950 4300 2900 4300
Wire Wire Line
	2900 4300 2900 4350
Wire Wire Line
	2900 4400 2950 4400
Wire Wire Line
	2900 4350 2850 4350
Connection ~ 2900 4350
Wire Wire Line
	2900 4350 2900 4400
Wire Wire Line
	2850 4200 2950 4200
Wire Wire Line
	2950 4100 2850 4100
Wire Wire Line
	2850 4000 2950 4000
Wire Wire Line
	2950 3900 2850 3900
Wire Wire Line
	4100 1900 4100 1800
Wire Wire Line
	4100 1800 4200 1800
Wire Wire Line
	4200 1700 4100 1700
Wire Wire Line
	4100 1700 4100 1600
Wire Wire Line
	5700 1600 5700 1700
Wire Wire Line
	5700 1700 5800 1700
Wire Wire Line
	5800 1800 5700 1800
Wire Wire Line
	5700 1800 5700 1900
$Comp
L power:+5V #PWR0108
U 1 1 63641C56
P 8250 3450
F 0 "#PWR0108" H 8250 3300 50  0001 C CNN
F 1 "+5V" H 8265 3623 50  0000 C CNN
F 2 "" H 8250 3450 50  0001 C CNN
F 3 "" H 8250 3450 50  0001 C CNN
	1    8250 3450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 63643310
P 5700 1900
F 0 "#PWR0109" H 5700 1650 50  0001 C CNN
F 1 "GND" H 5705 1727 50  0000 C CNN
F 2 "" H 5700 1900 50  0001 C CNN
F 3 "" H 5700 1900 50  0001 C CNN
	1    5700 1900
	1    0    0    -1  
$EndComp
Text GLabel 4500 4500 2    50   Input ~ 0
M2
Text GLabel 4500 4600 2    50   Input ~ 0
M1
Text GLabel 4500 4700 2    50   Input ~ 0
M0
Text GLabel 4500 4400 2    50   Input ~ 0
DIR
Text GLabel 4500 4300 2    50   Input ~ 0
STEP
Text GLabel 4600 4100 2    50   Input ~ 0
EN
Wire Wire Line
	4400 4200 4450 4200
Wire Wire Line
	4450 4200 4450 4100
Wire Wire Line
	4450 4100 4400 4100
Wire Wire Line
	4450 4100 4600 4100
Connection ~ 4450 4100
Wire Wire Line
	4500 4300 4400 4300
Wire Wire Line
	4400 4400 4500 4400
Wire Wire Line
	4500 4500 4400 4500
Wire Wire Line
	4400 4600 4500 4600
Wire Wire Line
	4500 4700 4400 4700
$Comp
L power:+3.3V #PWR0110
U 1 1 636469AA
P 6800 3450
F 0 "#PWR0110" H 6800 3300 50  0001 C CNN
F 1 "+3.3V" H 6815 3623 50  0000 C CNN
F 2 "" H 6800 3450 50  0001 C CNN
F 3 "" H 6800 3450 50  0001 C CNN
	1    6800 3450
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0111
U 1 1 63647E6F
P 4700 5000
F 0 "#PWR0111" H 4700 4850 50  0001 C CNN
F 1 "+3.3V" H 4715 5173 50  0000 C CNN
F 2 "" H 4700 5000 50  0001 C CNN
F 3 "" H 4700 5000 50  0001 C CNN
	1    4700 5000
	0    1    1    0   
$EndComp
Wire Wire Line
	4400 5000 4700 5000
Wire Wire Line
	6800 3450 6800 3650
Wire Wire Line
	6800 3650 7100 3650
Wire Wire Line
	8000 3650 8250 3650
Wire Wire Line
	8250 3450 8250 3550
Wire Wire Line
	8250 3550 8000 3550
Text GLabel 8100 4050 2    50   Input ~ 0
EN
Text GLabel 8100 3950 2    50   Input ~ 0
DIR
Text GLabel 8100 3850 2    50   Input ~ 0
STEP
Text GLabel 8100 4350 2    50   Input ~ 0
M0
Text GLabel 8100 4250 2    50   Input ~ 0
M1
Text GLabel 8100 4150 2    50   Input ~ 0
M2
Wire Wire Line
	8000 3850 8100 3850
Wire Wire Line
	8100 3950 8000 3950
Wire Wire Line
	8000 4050 8100 4050
Wire Wire Line
	8100 4150 8000 4150
Wire Wire Line
	8000 4250 8100 4250
Wire Wire Line
	8100 4350 8000 4350
$Comp
L Connector:Conn_01x02_Female J2
U 1 1 6361E597
P 4400 1700
F 0 "J2" H 4428 1676 50  0000 L CNN
F 1 "Conn_01x02_Female" H 4428 1585 50  0000 L CNN
F 2 "TerminalBlock_TE-Connectivity:TerminalBlock_TE_282834-2_1x02_P2.54mm_Horizontal" H 4400 1700 50  0001 C CNN
F 3 "~" H 4400 1700 50  0001 C CNN
	1    4400 1700
	1    0    0    -1  
$EndComp
$Comp
L Breakouts:Adafruit_ItsyBitsy_M4_Express U2
U 1 1 63624B99
P 7550 3450
F 0 "U2" H 7550 3615 50  0000 C CNN
F 1 "Adafruit_ItsyBitsy_M4_Express" H 7550 3524 50  0000 C CNN
F 2 "Modules:Adafruit_ItsyBitsy_M4" H 7550 3650 50  0001 C CNN
F 3 "" H 7550 3650 50  0001 C CNN
	1    7550 3450
	1    0    0    -1  
$EndComp
$EndSCHEMATC
