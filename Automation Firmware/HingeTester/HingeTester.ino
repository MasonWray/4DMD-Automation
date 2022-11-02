/*
 Name:		HingeTester.ino
 Created:	10/26/2022 7:48:02 PM
 Author:	Mason Wray
*/

#define EN_PIN 11
#define DR_PIN 12
#define ST_PIN 13
#define M1_PIN 7
#define M2_PIN 9
#define M3_PIN 10

#define CONFIG_FILE "data.csv"

#include <Adafruit_DotStar.h>
#include <SPI.h>
#include <SdFat.h>
#include <Adafruit_SPIFlash.h>

#include "src/StatusIndicator.h"
#include "src/flash_config.h"

Adafruit_DotStar ds = Adafruit_DotStar(1, 8, 6, DOTSTAR_BGR);
StatusIndicator status = StatusIndicator(&ds);

Adafruit_SPIFlash flash(&flashTransport);
FatVolume fatfs;

const bool req_serial = false;

const int num_steps = 5000;
const int period = 500;
const int interval = 1;

bool dir = false;
int pos = 0;

void setup()
{
	pinMode(M1_PIN, OUTPUT);
	pinMode(M2_PIN, OUTPUT);
	pinMode(M3_PIN, OUTPUT);
	digitalWrite(M1_PIN, HIGH);
	digitalWrite(M2_PIN, HIGH);
	digitalWrite(M3_PIN, HIGH);

	pinMode(EN_PIN, OUTPUT);
	pinMode(ST_PIN, OUTPUT);
	pinMode(DR_PIN, OUTPUT);
	digitalWrite(EN_PIN, HIGH);
	digitalWrite(DR_PIN, HIGH);
	dir = true;

	status.begin();
	status.set(StatusIndicator::STARTING);

	Serial.begin(115200);
	if (req_serial)
	{
		while (!Serial)
		{
			status.update();
		}
	}

	if (!flash.begin())
	{
		Serial.println("Error, failed to initialize flash chip!");
		status.set(StatusIndicator::ERR);
		while (1) status.update();
	}

	Serial.print("JEDEC ID: 0x");
	Serial.println(flash.getJEDECID(), HEX);
	Serial.print("Flash size: ");
	Serial.print(flash.size() / 1024);
	Serial.println(" KB");

	if (!fatfs.begin(&flash))
	{
		Serial.println("Error, failed to mount newly formatted filesystem!");
		Serial.println("Was the flash chip formatted with the fatfs_format example?");
		status.set(StatusIndicator::ERR);
		while (1) status.update();
	}
	status.set(StatusIndicator::NORMAL);
	Serial.println("MobileDemand Hinge Failure Tester");

	File32 dataFile = fatfs.open(CONFIG_FILE, FILE_WRITE);
	if (dataFile)
	{
		dataFile.print("Hello!\n");
		dataFile.close();
		Serial.println("Wrote new data to file!");
	}
	else
	{
		status.set(StatusIndicator::ERR);
	}

	File32 readFile = fatfs.open(CONFIG_FILE, FILE_READ);
	if (!readFile) {
		Serial.println("Error, failed to open for reading!");
		while (1) yield();
	}
	String line = readFile.readStringUntil('\n');
	Serial.print(F("First line of test.txt: ")); Serial.println(line);
}

void step()
{
	digitalWrite(ST_PIN, HIGH);
	delayMicroseconds(period);
	digitalWrite(ST_PIN, LOW);
}

void loop()
{
	Serial.println(pos);
	if (pos <= 0)
	{
		Serial.println("bottom");
		pos = 0;
		dir = true;
		digitalWrite(DR_PIN, HIGH);
		status.set(StatusIndicator::NORMAL);
	}

	if (pos >= num_steps)
	{
		Serial.println("top");
		pos = num_steps;
		dir = false;
		digitalWrite(DR_PIN, LOW);
		status.set(StatusIndicator::WARN);
	}

	if (dir)
	{
		pos++;
	}
	else
	{
		pos--;
	}

	step();
	status.update();

	delay(interval);
}
