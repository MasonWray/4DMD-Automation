/*
 Name:		HingeTester.ino
 Created:	10/26/2022 7:48:02 PM
 Author:	Mason Wray
*/

#define EN_PIN 11
#define DR_PIN 12
#define ST_PIN 13
#define M0_PIN 7
#define M1_PIN 9
#define M2_PIN 10

#define CONFIG_FILE "data.csv"
#define SERIAL_DELAY 15000

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

const int startup = 500;
const int num_steps = 800;
const int period = 10;
const int interval_base = 150;
const int interval_variance = 1000;

bool dir = false;
int pos = 0;

bool enter_config = false;

void setup()
{
	// Configure microstepping
	pinMode(M0_PIN, OUTPUT);
	pinMode(M1_PIN, OUTPUT);
	pinMode(M2_PIN, OUTPUT);
	digitalWrite(M0_PIN, HIGH);
	digitalWrite(M1_PIN, LOW);
	digitalWrite(M2_PIN, HIGH);

	// Configure driver step pins
	pinMode(EN_PIN, OUTPUT);
	pinMode(ST_PIN, OUTPUT);
	pinMode(DR_PIN, OUTPUT);
	delay(startup);
	digitalWrite(EN_PIN, HIGH);
	digitalWrite(DR_PIN, HIGH);
	dir = true;

	// Start status LED controller
	status.begin();
	status.set(StatusIndicator::STARTING);

	// Wait for serial connection
	Serial.begin(115200);
	int serial_timer = millis();
	while (millis() - serial_timer < SERIAL_DELAY)
	{
		status.update();
		if (Serial)
		{
			enter_config = true;
			break;
		}
	}

	// Initialize flash chip
	if (!flash.begin())
	{
		Serial.println("Error, failed to initialize flash chip!");
		status.set(StatusIndicator::ERR);
		while (1) status.update();
	}

	if (!fatfs.begin(&flash))
	{
		Serial.println("Error, failed to mount newly formatted filesystem!");
		Serial.println("Was the flash chip formatted with the fatfs_format example?");
		status.set(StatusIndicator::ERR);
		while (1) status.update();
	}

	status.set(StatusIndicator::NORMAL);
	Serial.println("MobileDemand Hinge Failure Tester");

	/*File32 dataFile = fatfs.open(CONFIG_FILE, FILE_WRITE);
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
	if (!readFile)
	{
		Serial.println("Error, failed to open for reading!");
		while (1) yield();
	}
	String line = readFile.readStringUntil('\n');
	Serial.print(F("First line of test.txt: ")); Serial.println(line);*/
}

void step()
{
	digitalWrite(ST_PIN, HIGH);
	delayMicroseconds(period);
	digitalWrite(ST_PIN, LOW);
}

int calcDelay(int period, int base, int variance, int length, int pos)
{
	double x = (double)pos / (double)length;
	double adj = ((cos(2.0 * PI * x) / 2.0) + 0.5) * (double)variance;
	return base + round(adj) - period;
}

void loop()
{
	// Enter REPL is serial connection exists
	if (enter_config)
	{

	}

	// Start operation is confic session is not requested
	else
	{
		if (pos <= 0)
		{
			pos = 0;
			dir = true;
			digitalWrite(DR_PIN, HIGH);
			status.set(StatusIndicator::NORMAL);
		}

		if (pos >= num_steps)
		{
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
		int t = calcDelay(period, interval_base, interval_variance, num_steps, pos);
		delayMicroseconds(t);
	}
}
